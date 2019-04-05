/**
* @file static_model.h
* @brief �A�j���[�V�����Ȃ����f���N���X
* @author �ΎR�@�I
* @date 2019/03/18
*/
#pragma once
#include "manager/static_model_manager.h"
#include "../../command_list/Bundle/bundle.h"
#include <memory>

/**
* @brief �A�j���[�V�����Ȃ����f���N���X
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