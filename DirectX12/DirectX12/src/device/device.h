/**
* @file device.h
* @brief �e�f�o�C�X���Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief �e�f�o�C�X���Ǘ�����N���X
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
	//���\�[�X�o���A
	void SetResourceBarrier
	(D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after,
		ID3D12Resource* resource, ComPtr<ID3D12GraphicsCommandList>& com_command_list);

	//�R�}���h�̎��s
	HRESULT ExecuteCommand
	(ComPtr<ID3D12GraphicsCommandList>& com_command_list, 
		ComPtr<ID3D12CommandAllocator>& com_command_allocator, 
		ID3D12PipelineState* p_pipeline);

	//�Q�b�^
	ComPtr<ID3D12Device>& GetDevice();
	ComPtr<ID3D12GraphicsCommandList>& GetCommandList();
	ComPtr<ID3D12RootSignature>& GetRootSignature();
};