/**
* @file bundle.h
* @brief �o���h���N���X
* @author �ΎR�@�I
* @date 2019/03/11
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"

/**
* @brief �o���h���N���X
*/
class Bundle
{
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList(ComPtr<ID3D12PipelineState>& com_pipeline);
public:
	HRESULT Init(ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT Close();
	void SetExecuteCommandList(ComPtr<ID3D12GraphicsCommandList>& execute_command_list);
	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
};