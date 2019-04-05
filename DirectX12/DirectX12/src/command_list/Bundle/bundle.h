/**
* @file bundle.h
* @brief バンドルクラス
* @author 石山　悠
* @date 2019/03/11
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <memory>

/**
* @brief バンドルクラス
*/
class Bundle
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Bundle();
	~Bundle()noexcept;
	Bundle(Bundle&&)noexcept;
	Bundle& operator=(Bundle&&)noexcept;
	HRESULT Init(ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT Close();
	void SetExecuteCommandList(ComPtr<ID3D12GraphicsCommandList>& execute_command_list);
	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
};