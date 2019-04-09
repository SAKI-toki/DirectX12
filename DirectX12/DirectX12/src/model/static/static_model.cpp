/**
* @file static_model.cpp
* @brief アニメーションなしモデルクラスの関数定義
* @author 石山　悠
* @date 2019/03/18
*/
#include "static_model.h"
#include "../../common/message_box.h"
#include "../../camera/camera.h"
#include "../../device/device.h"
#include "../../light/directional/directional_light.h"

/**
* @brief アニメーションなしモデルクラスのpimplイディオム
*/
class StaticModel::Impl
{
public:
	/**
	* @brief アニメーションなしモデルクラスの定数構造体
	*/
	struct StaticModelConstant
	{
		Matrix m;
		Matrix world;
		//Float4 light;
		Float4 col;
	};
	//モデルのキー
	std::wstring key;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	Bundle bundle;
	HRESULT SetBundle();
	HRESULT UpdateTransform(const Transform& transform);
};

#pragma region public

/**
* @brief アニメーションなしモデルクラスのコンストラクタ
*/
StaticModel::StaticModel() :
	pimpl(new Impl{})
{}

//デストラクタ、ムーブコンストラクタ、ムーブ代入演算子のデフォルト指定
StaticModel::~StaticModel()noexcept = default;
StaticModel::StaticModel(StaticModel&&)noexcept = default;
StaticModel& StaticModel::operator=(StaticModel&&)noexcept = default;

/**
* @brief アニメーションなしモデルクラスの初期化
* @param model_path モデルのパス
* @param pipeline 描画するパイプライン
* @return 成功したかどうか
*/
HRESULT StaticModel::Init(const std::wstring& model_path,
	ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	pimpl->key = model_path;
	hr = pimpl->CreateBuffer();
	if (FAILED(hr))return hr;
	hr = StaticModelManager::getinstance()->LoadModel(pimpl->key);
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Init(pipeline);
	if (FAILED(hr))return hr;
	hr = pimpl->SetBundle();
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Close();
	if (FAILED(hr))return hr;
	hr = pimpl->UpdateTransform({});
	if (FAILED(hr))return hr;
	hr = UpdateColor({ 1.0f,1.0f, 1.0f, 1.0f });
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief Colorの更新
* @param color 新しいColor
* @return 成功したかどうか
*/
HRESULT StaticModel::UpdateColor(const Float4& color)
{
	HRESULT hr = S_OK;

	StaticModel::Impl::StaticModelConstant* buf{};
	hr = pimpl->constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗",
			L"static_model.cpp/StaticModel::UpdateColor");
		return hr;
	}
	buf->col = color;
	pimpl->constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief モデルの描画
* @param transform 位置や回転、拡縮
* @param command_list 命令を送るコマンドリスト
* @return 成功したかどうか
*/
HRESULT StaticModel::Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& command_list)
{

	HRESULT hr = S_OK;

	hr = pimpl->UpdateTransform(transform);
	if (FAILED(hr))return hr;
	pimpl->bundle.SetExecuteCommandList(command_list);

	return hr;
}

unsigned int StaticModel::GetPolygonNum()
{
	return StaticModelManager::getinstance()->GetPolygonNum(pimpl->key);
}

#pragma endregion

#pragma region private

/**
* @brief バッファの作成
* @return 成功したかどうか
*/
HRESULT StaticModel::Impl::CreateBuffer()
{
	HRESULT hr = S_OK;

	D3D12_HEAP_PROPERTIES heap_properties{};
	heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resource_desc.Width = 256;
	resource_desc.Height = 1;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 1;
	resource_desc.Format = DXGI_FORMAT_UNKNOWN;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;

	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constant_buffer));
	if (FAILED(hr))
	{
		Comment(L"定数バッファ用のリソースとヒープの作成に失敗",
			L"static_model.cpp/StaticModel::Impl::CreateBuffer");
		return hr;
	}

	return hr;
}

/**
* @brief バンドルにコマンドをセットする
* @return 成功したかどうか
*/
HRESULT StaticModel::Impl::SetBundle()
{
	HRESULT hr = S_OK;

	decltype(auto) bundle_command_list = bundle.GetCommandList();

	bundle_command_list->SetGraphicsRootSignature(Device::getinstance()->GetRootSignature().Get());
	//定数バッファをセット
	bundle_command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	//モデルの描画
	StaticModelManager::getinstance()->SetModel(key, bundle_command_list);

	return hr;
}

/**
* @brief Transformの更新
* @param transform 新しいTransform
* @return 成功したかどうか
*/
HRESULT StaticModel::Impl::UpdateTransform(const Transform& transform)
{
	HRESULT hr = S_OK;

	auto world = DirectX::XMMatrixIdentity();
	auto scale = transform.get_scale();
	Matrix scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	auto rot = transform.get_rot();
	Matrix rot_mat = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	auto pos = transform.get_pos();
	Matrix pos_mat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	world = world * scale_mat * rot_mat * pos_mat;

	Matrix mat = DirectX::XMMatrixTranspose(world * Camera::getinstance()->GetViewMulProjection());
	StaticModelConstant* buf{};
	hr = constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗",
			L"static_model.cpp/StaticModel::Impl::UpdateTransform");
		return hr;
	}
	buf->m = mat;
	buf->world = DirectX::XMMatrixTranspose(world);
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

#pragma endregion