/**
* @file static_model_manager.cpp
* @brief アニメーションなしモデルクラスの管理クラスの関数定義
* @author 石山　悠
* @date 2019/03/18
*/
#include "static_model_manager.h"
#include "../../../common/message_box.h"
#include "../../../device/device.h"
#include <fstream>
#include <unordered_map>

/**
* @brief アニメーションなしモデルクラスの管理クラスのpimplイディオム
*/
class StaticModelManager::Impl
{
public:
	/**
	* @brief 頂点情報
	*/
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
	};
	/**
	* @brief モデル情報
	*/
	struct MeshData
	{
		unsigned int polygon_num{};
		unsigned int index_num{};
		ComPtr<ID3D12Resource> vertex_buffer;
		D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view{};
		ComPtr<ID3D12Resource> index_buffer;
		D3D12_INDEX_BUFFER_VIEW index_buffer_view{};
	};
	std::unordered_map<std::wstring, std::vector<MeshData>> model_data_map;
};

#pragma region public

/**
* @brief アニメーションなしモデルクラスの管理クラスのコンストラクタ
*/
StaticModelManager::StaticModelManager() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
StaticModelManager::~StaticModelManager()noexcept = default;

/**
* @brief アニメーションなしモデルの読み込み
* @param path モデルのパス
* @return 成功したかどうか
*/
HRESULT StaticModelManager::LoadModel(const std::wstring& path)
{
	HRESULT hr = S_OK;

	auto itr = pimpl->model_data_map.find(path);
	//既に読み込んでいる場合
	if (itr != std::end(pimpl->model_data_map)) { return hr; }
	//独自ファイルの読み込み
	std::ifstream ifs(path, std::ios_base::binary);
	if (ifs.fail())
	{
		Comment(L"モデルのパスが違います",
			L"static_model_manager.cpp/StaticModelManager::LoadModel");
		return E_FAIL;
	}
	unsigned int mesh_num;
	ifs.read(reinterpret_cast<char*>(&mesh_num), sizeof(mesh_num));
	std::vector<StaticModelManager::Impl::MeshData> mesh_data_list(mesh_num);
	for (unsigned int mesh_n = 0; mesh_n < mesh_num; ++mesh_n)
	{
		//各情報の数
		unsigned int index_num;
		ifs.read(reinterpret_cast<char*>(&index_num), sizeof(index_num));
		//各情報のリスト
		std::vector<Float3> pos_list(index_num);
		std::vector<Float3> nor_list(index_num);
		mesh_data_list[mesh_n].index_num = index_num;
		mesh_data_list[mesh_n].polygon_num = index_num / 3;
		{
			//頂点
			for (unsigned int i = 0; i < index_num; ++i)
			{
				ifs.read(reinterpret_cast<char*>(&pos_list[i].x), sizeof(pos_list[i].x));
				ifs.read(reinterpret_cast<char*>(&pos_list[i].y), sizeof(pos_list[i].y));
				ifs.read(reinterpret_cast<char*>(&pos_list[i].z), sizeof(pos_list[i].z));
			}
			//法線
			for (unsigned int i = 0; i < index_num; ++i)
			{
				ifs.read(reinterpret_cast<char*>(&nor_list[i].x), sizeof(nor_list[i].x));
				ifs.read(reinterpret_cast<char*>(&nor_list[i].y), sizeof(nor_list[i].y));
				ifs.read(reinterpret_cast<char*>(&nor_list[i].z), sizeof(nor_list[i].z));
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
		resource_desc.Width = sizeof(StaticModelManager::Impl::Vertex3D) * index_num;
		resource_desc.Height = 1;
		resource_desc.DepthOrArraySize = 1;
		resource_desc.MipLevels = 1;
		resource_desc.Format = DXGI_FORMAT_UNKNOWN;
		resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resource_desc.SampleDesc.Count = 1;
		resource_desc.SampleDesc.Quality = 0;

		hr = Device::getinstance()->GetDevice()->CreateCommittedResource
		(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&mesh_data_list[mesh_n].vertex_buffer));
		if (FAILED(hr))
		{
			Comment(L"頂点バッファ用のリソースとヒープの作成に失敗",
				L"static_model_manager.cpp/StaticModelManager::LoadModel");
			return hr;
		}
		mesh_data_list[mesh_n].vertex_buffer_view.BufferLocation = 
			mesh_data_list[mesh_n].vertex_buffer->GetGPUVirtualAddress();
		mesh_data_list[mesh_n].vertex_buffer_view.StrideInBytes = sizeof(StaticModelManager::Impl::Vertex3D);
		mesh_data_list[mesh_n].vertex_buffer_view.SizeInBytes = sizeof(StaticModelManager::Impl::Vertex3D) * index_num;

		resource_desc.Width = sizeof(UINT32) * mesh_data_list[mesh_n].index_num;
		hr = Device::getinstance()->GetDevice()->CreateCommittedResource
		(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&mesh_data_list[mesh_n].index_buffer));
		if (FAILED(hr))
		{
			Comment(L"インデックスバッファ用のリソースとヒープの作成に失敗",
				L"static_model_manager.cpp/StaticModelManager::LoadModel");
			return hr;
		}

		mesh_data_list[mesh_n].index_buffer_view.BufferLocation = 
			mesh_data_list[mesh_n].index_buffer->GetGPUVirtualAddress();
		mesh_data_list[mesh_n].index_buffer_view.SizeInBytes = 
			sizeof(UINT32) * mesh_data_list[mesh_n].index_num;
		mesh_data_list[mesh_n].index_buffer_view.Format = DXGI_FORMAT_R32_UINT;

		//頂点
		{
			StaticModelManager::Impl::Vertex3D *vb{};
			hr = mesh_data_list[mesh_n].vertex_buffer->Map(0, nullptr, reinterpret_cast<void**>(&vb));
			if (FAILED(hr))
			{
				delete[](vb);
				Comment(L"頂点バッファのMapに失敗",
					L"static_model_manager.cpp/StaticModelManager::LoadModel");
				return hr;
			}

			for (unsigned int i = 0; i < index_num; ++i)
			{
				vb[i] = StaticModelManager::Impl::Vertex3D{ pos_list[i],nor_list[i] };
			}

			mesh_data_list[mesh_n].vertex_buffer->Unmap(0, nullptr);
			vb = nullptr;
		}
		//インデックス
		{
			unsigned int *ib{};
			hr = mesh_data_list[mesh_n].index_buffer->Map(0, nullptr, reinterpret_cast<void**>(&ib));
			if (FAILED(hr))
			{
				Comment(L"インデックスバッファのMapに失敗",
					L"static_model_manager.cpp/StaticModelManager::LoadModel");
				return hr;
			}
			for (unsigned int i = 0; i < index_num; ++i)
			{
				ib[i] = i;
			}
			mesh_data_list[mesh_n].index_buffer->Unmap(0, nullptr);
			ib = nullptr;
		}

	}
	pimpl->model_data_map.insert(std::make_pair(path, mesh_data_list));

	return hr;
}

/**
* @brief アニメーションなしモデルをコマンドリストにセット
* @param key キー
* @param command_list セットするコマンドリスト
*/
void StaticModelManager::SetModel(const std::wstring& key,
	ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	auto itr = pimpl->model_data_map.find(key);
	if (itr == pimpl->model_data_map.end())throw 0;
	for (auto&& data : itr->second)
	{
		command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		command_list->IASetVertexBuffers(0, 1, &data.vertex_buffer_view);
		command_list->IASetIndexBuffer(&data.index_buffer_view);

		//描画
		command_list->DrawIndexedInstanced(data.index_num, 1, 0, 0, 0);
	}
}

/**
* @brief アニメーションなしモデルのポリゴン数を取得
* @param key キー
* @return ポリゴン数
*/
unsigned int StaticModelManager::GetPolygonNum(const std::wstring& key)
{
	unsigned int sum = 0;
	auto itr = pimpl->model_data_map.find(key);
	if (itr == pimpl->model_data_map.end())throw 0;
	for (auto&& data : itr->second)
	{
		sum += data.polygon_num;
	}
	return sum;
}

#pragma endregion