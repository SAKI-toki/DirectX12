/**
* @file execute_command_list.h
* @brief 実行用コマンドリストクラス
* @author 石山　悠
* @date 2019/03/11
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <memory>

/**
* @brief 実行用のコマンドリスト
*/
class ExecuteCommandList
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
protected:
	//継承し、そのオブジェクトにあったパイプラインを作成する
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