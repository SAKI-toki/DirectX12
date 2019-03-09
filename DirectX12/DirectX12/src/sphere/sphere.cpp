#include "sphere.h"
#include "../camera/camera.h"
#include "../device/device.h"
#include "../common/message_box.h"
#include <saki/math.h>

HRESULT Sphere::Init(Float4 color)
{
	HRESULT hr = S_OK;

	hr = pipeline.CreatePipeline("SingleColor3D", L"resources/shader/SingleColor3D.hlsl",
		L"resources/shader/SingleColor3D.hlsl", true, true);
	if (FAILED(hr))return hr;
	hr = CreateBuffer();
	if (FAILED(hr))return hr;
	hr = CreateSphere();
	if (FAILED(hr))return hr;
	hr = UpdateColor(color);
	if (FAILED(hr))return hr;

	return hr;
}

HRESULT Sphere::UpdateTransform(const Transform& transform)
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
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗", L"sphere.cpp/Sphere::UpdateConstantBuffer");
		return hr;
	}
	buf->m = mat;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

HRESULT Sphere::UpdateColor(const Float4& color)
{
	HRESULT hr = S_OK;

	SphereConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗", L"sphere.cpp/Sphere::UpdateConstantBuffer");
		return hr;
	}
	buf->col = color;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

HRESULT Sphere::Draw(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	//定数バッファをセット
	command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	//パイプラインのセット
	pipeline.SetPipeline(command_list);

	command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);
	command_list->IASetIndexBuffer(&index_buffer_view);

	//描画
	command_list->DrawIndexedInstanced((VERT_NUM - 1) * ARC_NUM * 6, 1, 0, 0, 0);

	return hr;
}

HRESULT Sphere::CreateBuffer()
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
	resource_desc.Width = sizeof(Vertex3D) * VERT_NUM * ARC_NUM;
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
	vertex_buffer_view.SizeInBytes = sizeof(Vertex3D) * VERT_NUM * ARC_NUM;

	//インデックスの数
	resource_desc.Width = sizeof(WORD) * (VERT_NUM - 1) * ARC_NUM * 6;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&index_buffer));
	if (FAILED(hr))
	{
		Comment(L"インデックスバッファ用のリソースとヒープの作成に失敗", L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}

	index_buffer_view.BufferLocation = index_buffer->GetGPUVirtualAddress();
	index_buffer_view.SizeInBytes = sizeof(WORD) * (VERT_NUM - 1) * ARC_NUM * 6;
	index_buffer_view.Format = DXGI_FORMAT_R16_UINT;

	return hr;
}

HRESULT Sphere::CreateSphere()
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
		hr = index_buffer->Map(0, nullptr, (void**)&ib);
		if (FAILED(hr))
		{
			Comment(L"インデックスバッファのMapに失敗", L"cube.cpp/Cube::CreateCube");
			return hr;
		}
		int idx{};
		for (int i = 0; i < ARC_NUM - 1; ++i)
		{
			for (int j = 0; j < VERT_NUM - 1; ++j)
			{
				ib[0 + idx] = (VERT_NUM * i + j);
				ib[1 + idx] = (VERT_NUM * i + j + 1);
				ib[2 + idx] = (VERT_NUM * (i + 1) + j);
				ib[3 + idx] = (VERT_NUM * (i + 1) + j);
				ib[4 + idx] = (VERT_NUM * i + j + 1);
				ib[5 + idx] = (VERT_NUM * (i + 1) + j + 1);
				idx += 6;
			}
		}
		index_buffer->Unmap(0, nullptr);
		ib = nullptr;
	}
	return hr;
}