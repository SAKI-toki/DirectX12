#pragma once
#include "../../../../common/d3d12.h"
#include "../../../../common/alias.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>

class ObjModelManager :public saki::singleton<ObjModelManager>
{
	friend class ObjModel;
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
		Float2 uv;
	};
	struct ObjModelData
	{
		unsigned int index_num;
		ComPtr<ID3D12Resource> vertex_buffer;
		D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
		ComPtr<ID3D12Resource> index_buffer;
		D3D12_INDEX_BUFFER_VIEW index_buffer_view;
	};
	std::unordered_map<std::wstring, ObjModelData> obj_data_map;
	HRESULT LoadObjModel(const std::wstring& path);
	void SetObjModel(const std::wstring& key,
		ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};