/**
* @file execute_command_list.h
* @brief ���s�p�R�}���h���X�g�N���X
* @author �ΎR�@�I
* @date 2019/03/11
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"

/**
* @brief ���s�p�̃R�}���h���X�g
*/
class ExecuteCommandList
{
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	ComPtr<ID3D12PipelineState> pipeline;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList();
protected:
	//�p�����A���̃I�u�W�F�N�g�ɂ������p�C�v���C�����쐬����
	//�V�F�[�_�[���p����Œ�`���쐬����
	virtual HRESULT CreatePipeline() = 0;
public:
	HRESULT Init();
	HRESULT BeginScene();
	HRESULT Execute();

	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
	ComPtr<ID3D12PipelineState>& GetPipeline();

	virtual ~ExecuteCommandList() {}
};