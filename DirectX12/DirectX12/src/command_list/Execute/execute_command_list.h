/**
* @file execute_command_list.h
* @brief ���s�p�R�}���h���X�g�N���X
* @author �ΎR�@�I
* @date 2019/03/11
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <memory>

/**
* @brief ���s�p�̃R�}���h���X�g
*/
class ExecuteCommandList
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
protected:
	//�p�����A���̃I�u�W�F�N�g�ɂ������p�C�v���C�����쐬����
	virtual HRESULT CreatePipeline() = 0;
public:
	ExecuteCommandList();
	virtual ~ExecuteCommandList()noexcept;
	ExecuteCommandList(ExecuteCommandList&&)noexcept;
	ExecuteCommandList& operator=(ExecuteCommandList&&)noexcept;

	HRESULT Init();
	HRESULT BeginScene();
	HRESULT Execute();

	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
	ComPtr<ID3D12PipelineState>& GetPipeline();

};