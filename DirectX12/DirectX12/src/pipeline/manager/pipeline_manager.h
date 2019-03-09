/**
* @file pipeline_manager.h
* @brief パイプラインを管理するクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../../common/alias.h"
#include "../../common/d3d12.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>
class PipelineManager :public saki::singleton<PipelineManager>
{
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> pipeline_data_map;
	friend class Pipeline;
	HRESULT CreatePipeline(const std::string&, const WCHAR*, const WCHAR*, const bool, const bool);
	void SetPipeline(const std::string&, ComPtr<ID3D12GraphicsCommandList>&);
	ComPtr<ID3D12PipelineState>& GetPipeline(const std::string&);
};