/**
* @file sphere.cpp
* @brief スフィアクラスの関数定義
* @author 石山　悠
* @date 2019/03/12
*/
#include "sphere.h"
#include "../camera/camera.h"
#include "../device/device.h"
#include "../common/message_box.h"
#include "../texture/texture.h"
#include "../command_list/Bundle/bundle.h"
#include <saki/math.h>

/**
* @brief スフィアのpimplイディオム
*/
class Sphere::Impl
{
public:
	static constexpr int VERT_NUM = 32;//一つの弧を作る頂点の数
	static constexpr int ARC_NUM = 32;//球を作る弧の数
	/**
	* @brief 頂点情報
	*/
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
		Float2 uv;
	};
	/**
	* @brief 球体の定数構造体
	*/
	struct SphereConstant
	{
		Matrix m;
		Matrix world;
		//Float4 light;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
	ComPtr<ID3D12Resource> index_buffer;
	D3D12_INDEX_BUFFER_VIEW index_buffer_view;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateSphere();
	HRESULT CreateBuffer();
	Texture texture;
	Bundle bundle;
	HRESULT SetBundle();
	HRESULT UpdateTransform(const Transform& transform);
};

#pragma region public

/**
* @brief スフィアのコンストラクタ
*/
Sphere::Sphere() :
	pimpl(new Impl{})
{}

//デストラクタ、ムーブコンストラクタ、ムーブ代入演算子のデフォルト指定
Sphere::~Sphere()noexcept = default;
Sphere::Sphere(Sphere&&)noexcept = default;
Sphere& Sphere::operator=(Sphere&&)noexcept = default;

/**
* @brief スフィアの初期化
* @param path テクスチャのパス
* @param pipeline 描画するパイプライン
* @return 成功したかどうか
*/
HRESULT Sphere::Init(const std::wstring& path, ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	hr = pimpl->CreateBuffer();
	if (FAILED(hr))return hr;
	hr = pimpl->CreateSphere();
	if (FAILED(hr))return hr;
	hr = pimpl->texture.LoadTexture(path);
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Init(pipeline);
	if (FAILED(hr))return hr;
	hr = pimpl->SetBundle();
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Close();
	if (FAILED(hr))return hr;
	hr = pimpl->UpdateTransform({});
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief スフィアの描画
* @param transform 位置や回転、拡縮
* @param command_list 命令を送るコマンドリスト
* @return 成功したかどうか
*/
HRESULT Sphere::Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	hr = pimpl->UpdateTransform(transform);
	if (FAILED(hr))return hr;
	//テクスチャをセット
	pimpl->texture.SetTexture(command_list);
	pimpl->bundle.SetExecuteCommandList(command_list);

	return hr;
}

#pragma endregion

#pragma region pimpl

/**
* @brief バッファの作成
* @return 成功したかどうか
*/
HRESULT Sphere::Impl::CreateBuffer()
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
			L"sphere.cpp/Cube::CreateBuffer");
		return hr;
	}

	//頂点の数
	resource_desc.Width = sizeof(Vertex3D) * VERT_NUM * ARC_NUM;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertex_buffer));
	if (FAILED(hr))
	{
		Comment(L"頂点バッファ用のリソースとヒープの作成に失敗", 
			L"sphere.cpp/Cube::CreateBuffer");
		return hr;
	}
	vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	vertex_buffer_view.StrideInBytes = sizeof(Vertex3D);
	vertex_buffer_view.SizeInBytes = sizeof(Vertex3D) * VERT_NUM * ARC_NUM;

	//インデックスの数
	resource_desc.Width = sizeof(WORD) * (VERT_NUM - 1) * ARC_NUM * 6;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&index_buffer));
	if (FAILED(hr))
	{
		Comment(L"インデックスバッファ用のリソースとヒープの作成に失敗",
			L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}

	index_buffer_view.BufferLocation = index_buffer->GetGPUVirtualAddress();
	index_buffer_view.SizeInBytes = sizeof(WORD) * (VERT_NUM - 1) * ARC_NUM * 6;
	index_buffer_view.Format = DXGI_FORMAT_R16_UINT;

	return hr;
}

/**
* @brief スフィアの作成
* @return 成功したかどうか
*/
HRESULT Sphere::Impl::CreateSphere()
{
	HRESULT hr = S_OK;
	//頂点の設定
	{
		Vertex3D *vb{};
		hr = vertex_buffer->Map(0, nullptr, reinterpret_cast<void**>(&vb));
		if (FAILED(hr))
		{
			delete[](vb);
			Comment(L"頂点バッファのMapに失敗",
				L"cube.cpp/Cube::CreateCube");
			return hr;
		}
		constexpr float pd = 2.0f * saki::PI<float> / (ARC_NUM - 1);
		constexpr float td = saki::PI<float> / (VERT_NUM - 1);
		float phi = 0.0f;
		for (int i = 0; i < ARC_NUM; ++i)
		{
			float t{};
			for (int j = 0; j < VERT_NUM; ++j)
			{
				vb[i * VERT_NUM + j].pos = { sinf(t) * cosf(phi), cosf(t), sinf(t) * sinf(phi) };
				vb[i * VERT_NUM + j].nor = vb[i * VERT_NUM + j].pos;//半径1の球なので、座標がそのまま法線として使える
				vb[i * VERT_NUM + j].uv = { i / (float)(ARC_NUM - 1), j / (float)(VERT_NUM - 1) };
				t += td;
			}

			phi += pd;
		}
		vertex_buffer->Unmap(0, nullptr);
		vb = nullptr;
	}
	//インデックスの設定
	{
		WORD *ib{};
		hr = index_buffer->Map(0, nullptr, reinterpret_cast<void**>(&ib));
		if (FAILED(hr))
		{
			Comment(L"インデックスバッファのMapに失敗", 
				L"cube.cpp/Cube::CreateCube");
			return hr;
		}
		int idx{};
		for (int i = 0; i < ARC_NUM - 1; ++i)
		{
			for (int j = 0; j < VERT_NUM - 1; ++j)
			{
				ib[0 + idx] = static_cast<WORD>(VERT_NUM * i + j);
				ib[1 + idx] = static_cast<WORD>(VERT_NUM * i + j + 1);
				ib[2 + idx] = static_cast<WORD>(VERT_NUM * (i + 1) + j);
				ib[3 + idx] = static_cast<WORD>(VERT_NUM * (i + 1) + j);
				ib[4 + idx] = static_cast<WORD>(VERT_NUM * i + j + 1);
				ib[5 + idx] = static_cast<WORD>(VERT_NUM * (i + 1) + j + 1);
				idx += 6;
			}
		}
		index_buffer->Unmap(0, nullptr);
		ib = nullptr;
	}
	return hr;
}

/**
* @brief バンドルにコマンドをセットする
* @return 成功したかどうか
*/
HRESULT Sphere::Impl::SetBundle()
{
	HRESULT hr = S_OK;

	decltype(auto) bundle_command_list = bundle.GetCommandList();

	bundle_command_list->SetGraphicsRootSignature(Device::getinstance()->GetRootSignature().Get());

	//定数バッファをセット
	bundle_command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	bundle_command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	bundle_command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);
	bundle_command_list->IASetIndexBuffer(&index_buffer_view);

	//描画
	bundle_command_list->DrawIndexedInstanced((VERT_NUM - 1) * ARC_NUM * 6, 1, 0, 0, 0);

	return hr;
}

/**
* @brief Transformの更新
* @param transform 新しいTransform
* @return 成功したかどうか
*/
HRESULT Sphere::Impl::UpdateTransform(const Transform& transform)
{
	HRESULT hr = S_OK;

	auto scale = transform.get_scale();
	Matrix scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	auto rot = transform.get_rot();
	Matrix rot_mat = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	auto pos = transform.get_pos();
	Matrix pos_mat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	Matrix world = scale_mat * rot_mat * pos_mat;
	Matrix mat = DirectX::XMMatrixTranspose(world * Camera::getinstance()->GetViewMulProjection());
	SphereConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗", 
			L"sphere.cpp/Sphere::UpdateConstantBuffer");
		return hr;
	}
	buf->m = mat;
	buf->world = DirectX::XMMatrixTranspose(world);
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

#pragma endregion