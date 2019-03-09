/**
* @file cube.cpp
* @brief キューブクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "cube.h"
#include "../device/device.h"
#include "../camera/camera.h"
#include "../common/message_box.h"
#include <vector>

/**
* @brief キューブの初期化
* @param key テクスチャのキー
* @param path テクスチャのパス
* @return 成功したかどうか
*/
HRESULT Cube::Init(const std::string& key, const WCHAR* path)
{
	HRESULT hr = S_OK;

	hr = CreateBuffer();
	if (FAILED(hr))return hr;
	hr = CreateCube();
	if (FAILED(hr))return hr;

	hr = texture.LoadTexture(key, path);
	if (FAILED(hr))return hr;
	hr = pipeline.CreatePipeline("cube",
		L"resources/shader/SimpleShader3D.hlsl", 
		L"resources/shader/SimpleShader3D.hlsl", true, false);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief Transformの更新
* @param transform 新しいTransform
* @return 成功したかどうか
*/
HRESULT Cube::UpdateTransform(const Transform& transform)
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
	CubeConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗", L"cube.cpp/Cube::UpdateTransform");
		return hr;
	}
	buf->m = mat;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief キューブの描画
* @param command_list 命令を送るコマンドリスト
* @return 成功したかどうか
*/
HRESULT Cube::Draw(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	//定数バッファをセット
	command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	//テクスチャをセット
	texture.SetTexture(command_list);
	//パイプラインのセット
	pipeline.SetPipeline(command_list);

	command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);
	command_list->IASetIndexBuffer(&index_buffer_view);

	//描画
	command_list->DrawIndexedInstanced(36, 1, 0, 0, 0);

	return hr;
}

/**
* @brief バッファの作成
* @return 成功したかどうか
*/
HRESULT Cube::CreateBuffer()
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
		Comment(L"定数バッファ用のリソースとヒープの作成に失敗", L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}

	//頂点の数
	resource_desc.Width = sizeof(Vertex3D) * 24;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertex_buffer));
	if (FAILED(hr))
	{
		Comment(L"頂点バッファ用のリソースとヒープの作成に失敗", L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}
	vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	vertex_buffer_view.StrideInBytes = sizeof(Vertex3D);
	vertex_buffer_view.SizeInBytes = sizeof(Vertex3D) * 24;

	//インデックスの数
	resource_desc.Width = sizeof(WORD) * 36;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&index_buffer));
	if (FAILED(hr))
	{
		Comment(L"インデックスバッファ用のリソースとヒープの作成に失敗", L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}

	index_buffer_view.BufferLocation = index_buffer->GetGPUVirtualAddress();
	index_buffer_view.SizeInBytes = sizeof(WORD) * 36;
	index_buffer_view.Format = DXGI_FORMAT_R16_UINT;

	return hr;
}

/**
* @brief キューブの作成
* @return 成功したかどうか
*/
HRESULT Cube::CreateCube()
{
	HRESULT hr = S_OK;
	//頂点の設定
	{
		Vertex3D *vb{};
		hr = vertex_buffer->Map(0, nullptr, (void**)&vb);
		if (FAILED(hr))
		{
			delete[](vb);
			Comment(L"頂点バッファのMapに失敗", L"cube.cpp/Cube::CreateCube");
			return hr;
		}
		vb[0] = Vertex3D{ Float3{-0.5f,-0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{0,1} };
		vb[1] = Vertex3D{ Float3{-0.5f,0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{0,0} };
		vb[2] = Vertex3D{ Float3{0.5f,-0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{1,1} };
		vb[3] = Vertex3D{ Float3{0.5f,0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{1,0} };

		vb[4] = Vertex3D{ Float3{-0.5f,0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{0,0} };
		vb[5] = Vertex3D{ Float3{-0.5f,-0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{0,1} };
		vb[6] = Vertex3D{ Float3{0.5f,0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{1,0} };
		vb[7] = Vertex3D{ Float3{0.5f,-0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{1,1} };

		vb[8] = Vertex3D{ Float3{-0.5f,0.5f,0.5f},Float3{-1.0f,0.0f,0.0f},Float2{0,0} };
		vb[9] = Vertex3D{ Float3{-0.5f,0.5f,-0.5f},Float3{-1.0f,0.0f,0.0f},Float2{1,0} };
		vb[10] = Vertex3D{ Float3{-0.5f,-0.5f,0.5f},Float3{-1.0f,0.0f,0.0f},Float2{0,1} };
		vb[11] = Vertex3D{ Float3{-0.5f,-0.5f,-0.5f},Float3{-1.0f,0.0f,0.0f},Float2{1,1} };

		vb[12] = Vertex3D{ Float3{0.5f,0.5f,0.5f},Float3{1.0f,0.0f,0.0f},Float2{0,0} };
		vb[13] = Vertex3D{ Float3{0.5f,-0.5f,0.5f},Float3{1.0f,0.0f,0.0f},Float2{1,0} };
		vb[14] = Vertex3D{ Float3{0.5f,0.5f,-0.5f},Float3{1.0f,0.0f,0.0f},Float2{0,1} };
		vb[15] = Vertex3D{ Float3{0.5f,-0.5f,-0.5f},Float3{1.0f,0.0f,0.0f},Float2{1,1} };

		vb[16] = Vertex3D{ Float3{-0.5f,0.5f,0.5f},Float3{0.0f,1.0f,0.0f},Float2{0,0} };
		vb[17] = Vertex3D{ Float3{0.5f,0.5f,0.5f},Float3{0.0f,1.0f,0.0f},Float2{1,0} };
		vb[18] = Vertex3D{ Float3{-0.5f,0.5f,-0.5f},Float3{0.0f,1.0f,0.0f},Float2{0,1} };
		vb[19] = Vertex3D{ Float3{0.5f,0.5f,-0.5f},Float3{0.0f,1.0f,0.0f},Float2{1,1} };

		vb[20] = Vertex3D{ Float3{-0.5f,-0.5f,0.5f},Float3{0.0f,-1.0f,0.0f},Float2{0,0} };
		vb[21] = Vertex3D{ Float3{-0.5f,-0.5f,-0.5f},Float3{0.0f,-1.0f,0.0f},Float2{1,0} };
		vb[22] = Vertex3D{ Float3{0.5f,-0.5f,0.5f},Float3{0.0f,-1.0f,0.0f},Float2{0,1} };
		vb[23] = Vertex3D{ Float3{0.5f,-0.5f,-0.5f},Float3{0.0f,-1.0f,0.0f},Float2{1,1} };
		vertex_buffer->Unmap(0, nullptr);
		vb = nullptr;
	}
	//インデックスの設定
	{
		WORD *ib{};
		hr = index_buffer->Map(0, nullptr, (void**)&ib);
		if (FAILED(hr))
		{
			Comment(L"インデックスバッファのMapに失敗", L"cube.cpp/Cube::CreateCube");
			return hr;
		}
		ib[0] = 0; ib[1] = 1; ib[2] = 2; ib[3] = 3; ib[4] = 2; ib[5] = 1;
		ib[6] = 4; ib[7] = 5; ib[8] = 6; ib[9] = 7; ib[10] = 6; ib[11] = 5;
		ib[12] = 8; ib[13] = 9; ib[14] = 10; ib[15] = 11; ib[16] = 10; ib[17] = 9;
		ib[18] = 12; ib[19] = 13; ib[20] = 14; ib[21] = 15; ib[22] = 14; ib[23] = 13;
		ib[24] = 16; ib[25] = 17; ib[26] = 18; ib[27] = 19; ib[28] = 18; ib[29] = 17;
		ib[30] = 20; ib[31] = 21; ib[32] = 22; ib[33] = 23; ib[34] = 22; ib[35] = 21;
		index_buffer->Unmap(0, nullptr);
		ib = nullptr;
	}
	return hr;
}
