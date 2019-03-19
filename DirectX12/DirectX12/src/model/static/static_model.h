/**
* @file static_model.h
* @brief �A�j���[�V�����Ȃ����f���N���X
* @author �ΎR�@�I
* @date 2019/03/18
*/
#pragma once
#include "manager/static_model_manager.h"
#include "../../command_list/Bundle/bundle.h"

/**
* @brief �A�j���[�V�����Ȃ����f���N���X
*/
class StaticModel
{
	/**
	* @brief �A�j���[�V�����Ȃ����f���N���X�̒萔�\����
	*/
	struct StaticModelConstant
	{
		Matrix m;
		Matrix world;
		Float4 light;
		Float4 col;
	};
	//���f���̃L�[
	std::wstring key;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	Bundle bundle;
	HRESULT SetBundle();
public:
	HRESULT Init(const std::wstring& model_path,
		ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT UpdateTransform(const Transform& transform);
	HRESULT UpdateColor(const Float4& color);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};