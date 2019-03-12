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

class Device :public saki::singleton<Device>
{
	static constexpr UINT FrameNum = 2;
	static constexpr UINT FPS = 60;
	UINT64 frames{};
	UINT rtv_index{};

	//factory
	ComPtr<IDXGIFactory4> factory;
	HRESULT CreateFactory();
	//device
	ComPtr<ID3D12Device> device;
	HRESULT CreateDevice();
	//command_queue
	ComPtr<ID3D12CommandQueue> command_queue;
	HANDLE fence_event;
	ComPtr<ID3D12Fence> queue_fence;
	HRESULT CreateCommandQueue();
	//swap_chain
	ComPtr<IDXGISwapChain3> swap_chain;
	HRESULT CreateSwapChain(HWND hwnd);
	//command_allocator
	ComPtr<ID3D12CommandAllocator> command_allocator;
	HRESULT CreateCommandAllocator();
	//command_list
	ComPtr<ID3D12GraphicsCommandList> command_list;
	HRESULT CreateCommandList();
	//root_signature
	ComPtr<ID3D12RootSignature> root_signature;
	HRESULT CreateRootSignature();
	//render_target
	ComPtr<ID3D12Resource> render_targets[FrameNum];
	ComPtr<ID3D12DescriptorHeap> dh_rtv;
	D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle[FrameNum];
	HRESULT CreateRenderTargetView();
	//depth_stencil
	ComPtr<ID3D12Resource> depth_buffer;
	ComPtr<ID3D12DescriptorHeap> dh_dsv;
	D3D12_CPU_DESCRIPTOR_HANDLE dsv_handle;
	HRESULT CreateDepthStencilBuffer();

	D3D12_RECT scissor_rect;
	D3D12_VIEWPORT viewport;
	void CreateScissorRectViewPort();

	HRESULT WaitForPreviousFrame();
public:
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