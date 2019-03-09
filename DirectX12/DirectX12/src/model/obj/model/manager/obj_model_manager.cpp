#include "obj_model_manager.h"
#include "../../../../device/device.h"
#include "../../../../common/message_box.h"
#include <fstream>
#include <saki/vector.h>

HRESULT ObjModelManager::LoadObjModel(const std::string& key, const WCHAR* path)
{
	HRESULT hr = S_OK;

	auto itr = obj_data_map.find(key);
	//既に読み込んでいる場合
	if (itr != std::end(obj_data_map)) { return hr; }
	ObjModelData obj_data;
	//各情報の数
	unsigned int pos_num, nor_num, uv_num, index_num;
	//独自ファイルの読み込み
	std::ifstream ifs(path, std::ios_base::binary);
	if (ifs.fail())
	{
		Comment(L"モデルのパスが違います", L"obj_model_manager.cpp/ObjModelManager::LoadObjModel");
		return E_FAIL;
	}
	ifs.read(reinterpret_cast<char*>(&pos_num), sizeof(pos_num));
	ifs.read(reinterpret_cast<char*>(&nor_num), sizeof(nor_num));
	ifs.read(reinterpret_cast<char*>(&uv_num), sizeof(uv_num));
	ifs.read(reinterpret_cast<char*>(&index_num), sizeof(index_num));
	//各情報のリスト
	std::vector<Float3> pos_list(pos_num);
	std::vector<Float3> nor_list(nor_num);
	std::vector<Float2> uv_list(uv_num);
	std::vector<saki::vector3<unsigned int>> index_list(index_num);
	obj_data.index_num = index_num;
	{
		//頂点
		for (unsigned int i = 0; i < pos_num; ++i)
		{
			ifs.read(reinterpret_cast<char*>(&pos_list[i].x), sizeof(pos_list[i].x));
			ifs.read(reinterpret_cast<char*>(&pos_list[i].y), sizeof(pos_list[i].y));
			ifs.read(reinterpret_cast<char*>(&pos_list[i].z), sizeof(pos_list[i].z));
		}
		//法線
		for (unsigned int i = 0; i < nor_num; ++i)
		{
			ifs.read(reinterpret_cast<char*>(&nor_list[i].x), sizeof(nor_list[i].x));
			ifs.read(reinterpret_cast<char*>(&nor_list[i].y), sizeof(nor_list[i].y));
			ifs.read(reinterpret_cast<char*>(&nor_list[i].z), sizeof(nor_list[i].z));
		}
		//UV
		for (unsigned int i = 0; i < uv_num; ++i)
		{
			ifs.read(reinterpret_cast<char*>(&uv_list[i].x), sizeof(uv_list[i].x));
			ifs.read(reinterpret_cast<char*>(&uv_list[i].y), sizeof(uv_list[i].y));
		}
		//面
		for (unsigned int i = 0; i < index_num; ++i)
		{
			ifs.read(reinterpret_cast<char*>(&index_list[i].x), sizeof(index_list[i].x));
			ifs.read(reinterpret_cast<char*>(&index_list[i].y), sizeof(index_list[i].y));
			ifs.read(reinterpret_cast<char*>(&index_list[i].z), sizeof(index_list[i].z));
		}
	}

	D3D12_HEAP_PROPERTIES heap_properties{};
	heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resource_desc.Width = sizeof(Vertex3D) * index_num;
	resource_desc.Height = 1;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 1;
	resource_desc.Format = DXGI_FORMAT_UNKNOWN;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;

	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&obj_data.vertex_buffer));
	if (FAILED(hr))
	{
		Comment(L"頂点バッファ用のリソースとヒープの作成に失敗", L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}
	obj_data.vertex_buffer_view.BufferLocation = obj_data.vertex_buffer->GetGPUVirtualAddress();
	obj_data.vertex_buffer_view.StrideInBytes = sizeof(Vertex3D);
	obj_data.vertex_buffer_view.SizeInBytes = sizeof(Vertex3D) * index_num;

	resource_desc.Width = sizeof(UINT32) * obj_data.index_num;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&obj_data.index_buffer));
	if (FAILED(hr))
	{
		Comment(L"インデックスバッファ用のリソースとヒープの作成に失敗", L"cube.cpp/Cube::CreateBuffer");
		return hr;
	}

	obj_data.index_buffer_view.BufferLocation = obj_data.index_buffer->GetGPUVirtualAddress();
	obj_data.index_buffer_view.SizeInBytes = sizeof(UINT32) * obj_data.index_num;
	obj_data.index_buffer_view.Format = DXGI_FORMAT_R32_UINT;

	//頂点
	{
		Vertex3D *vb{};
		hr = obj_data.vertex_buffer->Map(0, nullptr, (void**)&vb);
		if (FAILED(hr))
		{
			delete[](vb);
			Comment(L"頂点バッファのMapに失敗", L"obj_manager.cpp/ObjManager::LoadModel");
			return hr;
		}

		for (unsigned int i = 0; i < index_num; ++i)
		{
			vb[i] = Vertex3D{ pos_list[index_list[i].x],nor_list[index_list[i].y] ,uv_list[index_list[i].z] };
		}

		obj_data.vertex_buffer->Unmap(0, nullptr);
		vb = nullptr;
	}
	//インデックス
	{
		unsigned int *ib{};
		hr = obj_data.index_buffer->Map(0, nullptr, (void**)&ib);
		if (FAILED(hr))
		{
			Comment(L"インデックスバッファのMapに失敗", L"obj_manager.cpp/ObjManager::LoadModel");
			return hr;
		}
		for (unsigned int i = 0; i < index_num; ++i)
		{
			ib[i] = i;
		}
		obj_data.index_buffer->Unmap(0, nullptr);
		ib = nullptr;
	}

	obj_data_map.insert(std::make_pair(key, obj_data));

	return hr;
}

void ObjModelManager::SetObjModel(const std::string& key, ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	auto itr = obj_data_map.find(key);

	command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	command_list->IASetVertexBuffers(0, 1, &itr->second.vertex_buffer_view);
	command_list->IASetIndexBuffer(&itr->second.index_buffer_view);

	//描画
	command_list->DrawIndexedInstanced(itr->second.index_num, 1, 0, 0, 0);
}