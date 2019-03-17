/**
* @file static_model_manager.h
* @brief アニメーションなしモデルクラスの管理クラス
* @author 石山　悠
* @date 2019/03/18
*/
#pragma once
#include "../../../common/d3d12.h"
#include "../../../common/alias.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>

/**
* @brief アニメーションなしモデルクラスの管理クラス
*/
class StaticModelManager :public saki::singleton<StaticModelManager>
{
	friend class StaticModel;
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
	struct ModelData
	{
		unsigned int index_num;
		ComPtr<ID3D12Resource> vertex_buffer;
		D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
		ComPtr<ID3D12Resource> index_buffer;
		D3D12_INDEX_BUFFER_VIEW index_buffer_view;
	};
	std::unordered_map<std::wstring, std::vector<ModelData>> model_data_map;
	HRESULT LoadModel(const std::wstring&);
	void SetModel(const std::wstring& key,
		ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};