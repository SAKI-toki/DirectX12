/**
* @file pipeline.cpp
* @brief パイプラインクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "pipeline.h"

HRESULT Pipeline::CreatePipeline(const std::string& _key,
	const WCHAR* v_path, const WCHAR* p_path, const bool is_3d, const bool is_single_color)
{
	key = _key;
	return PipelineManager::getinstance()->CreatePipeline(key, v_path, p_path, is_3d, is_single_color);
}

void Pipeline::SetPipeline(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	PipelineManager::getinstance()->SetPipeline(key, command_list);
}

ComPtr<ID3D12PipelineState>& Pipeline::GetPipeline()
{
	return PipelineManager::getinstance()->GetPipeline(key);
}

std::string Pipeline::GetKey()const
{
	return key;
}
