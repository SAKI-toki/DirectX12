/**
* @file pipeline.h
* @brief パイプラインクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "manager/pipeline_manager.h"
class Pipeline
{
	std::string key;
public:
	HRESULT CreatePipeline(const std::string&, const WCHAR*, const WCHAR*, const bool, const bool);
	void SetPipeline(ComPtr<ID3D12GraphicsCommandList>&);
	ComPtr<ID3D12PipelineState>& GetPipeline();
	std::string GetKey()const;
};