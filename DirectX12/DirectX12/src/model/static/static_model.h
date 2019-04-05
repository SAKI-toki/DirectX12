/**
* @file static_model.h
* @brief アニメーションなしモデルクラス
* @author 石山　悠
* @date 2019/03/18
*/
#pragma once
#include "manager/static_model_manager.h"
#include "../../command_list/Bundle/bundle.h"
#include <memory>

/**
* @brief アニメーションなしモデルクラス
*/
class StaticModel
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	StaticModel();
	~StaticModel()noexcept;
	StaticModel(StaticModel&&)noexcept;
	StaticModel& operator=(StaticModel&&)noexcept;
	HRESULT Init(const std::wstring& model_path,
		ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT UpdateColor(const Float4& color);
	HRESULT Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& com_command_list);
	unsigned int GetPolygonNum();
};