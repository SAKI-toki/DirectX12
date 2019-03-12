/**
* @file execute_command_list.h
* @brief 実行用コマンドリストクラス
* @author 石山　悠
* @date 2019/03/11
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"

/**
* @brief 実行用のコマンドリスト
*/
class ExecuteCommandList
{
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	ComPtr<ID3D12PipelineState> pipeline;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList();
protected:
	//継承し、そのオブジェクトにあったパイプラインを作成する
	//シェーダーも継承先で定義し作成する
	virtual HRESULT CreatePipeline() = 0;
public:
	HRESULT Init();
	HRESULT BeginScene();
	HRESULT Execute();

	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
	ComPtr<ID3D12PipelineState>& GetPipeline();

	virtual ~ExecuteCommandList() {}
};