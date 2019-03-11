#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"

class ExecuteCommandList
{
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	ComPtr<ID3D12PipelineState> pipeline;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList();
protected:
	virtual HRESULT CreatePipeline() = 0;
public:
	HRESULT Init();

	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
	ComPtr<ID3D12PipelineState>& GetPipeline();

	virtual ~ExecuteCommandList() {}
};