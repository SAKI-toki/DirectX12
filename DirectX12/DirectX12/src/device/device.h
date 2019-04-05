/**
* @file device.h
* @brief 各デバイスを管理するクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief 各デバイスを管理するクラス
*/
class Device :public saki::singleton<Device>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Device();
	~Device()noexcept;

	HRESULT InitDevice(HWND hwnd);
	HRESULT BeginSceneSet(ComPtr<ID3D12GraphicsCommandList>& com_command_list);
	HRESULT BeginScene();
	HRESULT EndScene();
	HRESULT Present();
	//リソースバリア
	void SetResourceBarrier
	(D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after,
		ID3D12Resource* resource, ComPtr<ID3D12GraphicsCommandList>& com_command_list);

	//コマンドの実行
	HRESULT ExecuteCommand
	(ComPtr<ID3D12GraphicsCommandList>& com_command_list, 
		ComPtr<ID3D12CommandAllocator>& com_command_allocator, 
		ID3D12PipelineState* p_pipeline);

	//ゲッタ
	ComPtr<ID3D12Device>& GetDevice();
	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
	ComPtr<ID3D12RootSignature>& GetRootSignature();
};