/**
* @file sprite.cpp
* @brief スプライトクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "sprite.h"
#include "../device/device.h"
#include "../camera/camera.h"
#include "../common/message_box.h"

/**
* @brief スプライトの初期化
* @param path テクスチャのパス
* @param pipeline 描画するパイプライン
* @return 成功したかどうか
*/
HRESULT Sprite::Init(const std::wstring& path, ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	hr = CreateBuffer();
	if (FAILED(hr))return hr;
	hr = texture.LoadTexture(path);
	if (FAILED(hr))return hr;
	hr = CreatePlane();
	if (FAILED(hr))return hr;
	hr = bundle.Init(pipeline);
	if (FAILED(hr))return hr;
	hr = SetBundle();
	if (FAILED(hr))return hr;
	hr = bundle.Close();
	if (FAILED(hr))return hr;
	hr = UpdateTransform({});
	if (FAILED(hr))return hr;
	hr = UpdateColor({ 1.0f,1.0f,1.0f,1.0f });
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief Transformの更新
*/
HRESULT Sprite::UpdateTransform(const Transform& transform)
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
	SpriteConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗",
			L"sprite.cpp/Sprite::UpdateTransform");
		return hr;
	}
	buf->m = mat;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief Colorの更新
*/
HRESULT Sprite::UpdateColor(const Float4& color)
{
	HRESULT hr = S_OK;

	SpriteConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗",
			L"sprite.cpp/Sprite::UpdateColor");
		return hr;
	}
	buf->col = color;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

HRESULT Sprite::Draw(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	//テクスチャをセット
	texture.SetTexture(command_list);
	command_list->ExecuteBundle(bundle.GetCommandList().Get());

	return hr;
}

HRESULT Sprite::CreateBuffer()
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
			L"sprite.cpp/Sprite::CreateBuffer");
		return hr;
	}

	resource_desc.Width = sizeof(Vertex2D) * 4;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertex_buffer));
	if (FAILED(hr))
	{
		Comment(L"頂点バッファ用のリソースとヒープの作成に失敗",
			L"sprite.cpp/Sprite::CreateBuffer");
		return hr;
	}
	vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	vertex_buffer_view.StrideInBytes = sizeof(Vertex2D);
	vertex_buffer_view.SizeInBytes = sizeof(Vertex2D) * 4;

	return hr;
}

HRESULT Sprite::CreatePlane()
{
	HRESULT hr = S_OK;

	float texture_size_x = static_cast<float>(texture.GetWidth());
	float texture_size_y = static_cast<float>(texture.GetHeight());
	if (texture_size_x == -1.0f || texture_size_y == -1.0f)
	{
		Comment(L"正常にテクスチャのサイズを読み込めませんでした",
			L"sprite.cpp/Sprite::CreatePlane");
		return E_FAIL;
	}
	Vertex2D *vb{};
	hr = vertex_buffer->Map(0, nullptr, (void**)&vb);
	if (FAILED(hr))
	{
		delete[](vb);
		Comment(L"頂点バッファのMapに失敗", L"sprite.cpp/Sprite::CreatePlane");
		return hr;
	}
	vb[0] = Vertex2D{ Float3{-texture_size_x,-texture_size_y,0.0f},Float2{0,1} };
	vb[1] = Vertex2D{ Float3{-texture_size_x,+texture_size_y,0.0f},Float2{0,0} };
	vb[2] = Vertex2D{ Float3{+texture_size_x,-texture_size_y,0.0f},Float2{1,1} };
	vb[3] = Vertex2D{ Float3{+texture_size_x,+texture_size_y,0.0f},Float2{1,0} };
	vertex_buffer->Unmap(0, nullptr);
	vb = nullptr;

	return hr;
}

/**
* @brief バンドルにコマンドをセットする
* @return 成功したかどうか
*/
HRESULT Sprite::SetBundle()
{
	HRESULT hr = S_OK;

	decltype(auto) bundle_command_list = bundle.GetCommandList();

	bundle_command_list->SetGraphicsRootSignature(Device::getinstance()->GetRootSignature().Get());

	//定数バッファをセット
	bundle_command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	bundle_command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	bundle_command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);

	//描画
	bundle_command_list->DrawInstanced(4, 1, 0, 0);
	return hr;
}