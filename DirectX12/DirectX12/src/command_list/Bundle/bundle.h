#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"

class Bundle
{
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList();
public:
	HRESULT Init();
};