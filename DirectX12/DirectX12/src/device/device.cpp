/**
* @file device.cpp
* @brief �f�o�C�X�N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "device.h"
#include "../common/message_box.h"
#include "../common/window_size.h"

/**
* @brief �f�o�C�X�̏�����
* @param hwnd �E�B���h�E�n���h��
* @return �����������ǂ���
*/
HRESULT Device::InitDevice(HWND hwnd)
{
	HRESULT hr = S_OK;

	hr = CreateFactory();
	if (FAILED(hr))return hr;
	hr = CreateDevice();
	if (FAILED(hr))return hr;
	hr = CreateCommandQueue();
	if (FAILED(hr))return hr;
	hr = CreateSwapChain(hwnd);
	if (FAILED(hr))return hr;
	hr = CreateCommandAllocator();
	if (FAILED(hr))return hr;
	hr = CreateCommandList();
	if (FAILED(hr))return hr;
	hr = CreateRootSignature();
	if (FAILED(hr))return hr;
	hr = CreateRenderTargetView();
	if (FAILED(hr))return hr;
	hr = CreateDepthStencilBuffer();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �`��͂���
* @return �����������ǂ���
*/
HRESULT Device::BeginScene()
{
	HRESULT hr = S_OK;

	static constexpr float clear_color[4] = { 0.0f,0.0f,0.0f,1.0f };

	command_list->SetGraphicsRootSignature(root_signature.Get());

	command_list->RSSetViewports(1, &viewport);
	command_list->RSSetScissorRects(1, &scissor_rect);

	SetResourceBarrier(D3D12_RESOURCE_STATE_PRESENT, 
		D3D12_RESOURCE_STATE_RENDER_TARGET, render_targets[rtv_index].Get(), command_list);
	command_list->ClearDepthStencilView(dsv_handle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	command_list->ClearRenderTargetView(rtv_handle[rtv_index], clear_color, 0, nullptr);
	command_list->OMSetRenderTargets(1, &rtv_handle[rtv_index], true, &dsv_handle);

	return hr;
}

/**
* @brief �`��I���
* @return �����������ǂ���
*/
HRESULT Device::EndScene()
{
	HRESULT hr = S_OK;

	SetResourceBarrier(D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT, render_targets[rtv_index].Get(), command_list);

	hr = ExecuteCommand(command_list, command_allocator, nullptr);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief Present
* @return �����������ǂ���
*/
HRESULT Device::Present()
{
	HRESULT hr = S_OK;

	hr = swap_chain->Present(1, 0);
	if (FAILED(hr))
	{
		Comment(L"�X���b�v�`�F�C���̃v���[���g�Ɏ��s", L"device.cpp/Device::Present");
		return hr;
	}

	rtv_index = swap_chain->GetCurrentBackBufferIndex();

	return hr;
}

/**
* @brief ���\�[�X�o���A�̐ݒ�
*/
void Device::SetResourceBarrier(D3D12_RESOURCE_STATES before, D3D12_RESOURCE_STATES after, ID3D12Resource* resource, ComPtr<ID3D12GraphicsCommandList>& barrier_command_list)
{
	D3D12_RESOURCE_BARRIER resource_barrier{};

	resource_barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	resource_barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	resource_barrier.Transition.pResource = resource;
	resource_barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	resource_barrier.Transition.StateBefore = before;
	resource_barrier.Transition.StateAfter = after;
	barrier_command_list->ResourceBarrier(1, &resource_barrier);
	before = after;
}

/**
* @brief �R�}���h�̎��s
* @param execute_command_list ���s����R�}���h���X�g
* @param execute_command_allocator ���s����R�}���h�̃A���P�[�^
* @param reset_pipeline_state �R�}���h���X�g�̏������p�C�v���C��
* @return �����������ǂ���
*/
HRESULT Device::ExecuteCommand(
	ComPtr<ID3D12GraphicsCommandList>& execute_command_list,
	ComPtr<ID3D12CommandAllocator>& execute_command_allocator,
	ID3D12PipelineState* reset_pipeline_state)
{
	HRESULT hr = S_OK;

	hr = execute_command_list->Close();
	if (FAILED(hr))
	{
		Comment(L"�R�}���h���X�g��Close�Ɏ��s",
			L"device.cpp/Device::ExecuteCommand");
		return hr;
	}
	ID3D12CommandList *const command_lists = execute_command_list.Get();
	command_queue->ExecuteCommandLists(1, &command_lists);

	hr = WaitForPreviousFrame();
	if (FAILED(hr))return hr;

	hr = execute_command_allocator->Reset();
	if (FAILED(hr))
	{
		Comment(L"�R�}���h�A���P�[�^�[�̃��Z�b�g�Ɏ��s",
			L"device.cpp/Device::ExecuteCommand");
		return hr;
	}

	hr = execute_command_list->Reset(execute_command_allocator.Get(), reset_pipeline_state);
	if (FAILED(hr))
	{
		Comment(L"�R�}���h���X�g�̃��Z�b�g�Ɏ��s",
			L"device.cpp/Device::ExecuteCommand");
		return hr;
	}

	return hr;
}

/**
* @brief Factory�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateFactory()
{
	HRESULT hr = S_OK;
	UINT flg{};
#ifdef _DEBUG
	//�f�o�b�O���C���[
	{
		ComPtr<ID3D12Debug> debug;
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
		if (FAILED(hr))
		{
			Comment(L"�f�o�b�O�C���^�[�t�F�[�X�̎擾�Ɏ��s", L"device.cpp/Device::CreateFactory");
			return hr;
		}
		debug->EnableDebugLayer();
	}
	flg |= DXGI_CREATE_FACTORY_DEBUG;
#endif
	hr = CreateDXGIFactory2(flg, IID_PPV_ARGS(&factory));
	if (FAILED(hr))
	{
		Comment(L"factory�̍쐬�Ɏ��s", L"device.cpp/Device::CreateFactory");
		return hr;
	}

	return hr;
}

/**
* @brief Device�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateDevice()
{
	HRESULT hr = S_OK;
	ComPtr<IDXGIAdapter3> adapter;
	hr = factory->EnumAdapters(0, (IDXGIAdapter**)adapter.GetAddressOf());
	if (FAILED(hr))
	{
		Comment(L"�A�_�v�^��������܂���ł����B", L"device.cpp/Device::CreateDevice");
		return hr;
	}
	hr = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_1, IID_PPV_ARGS(&device));
	if (FAILED(hr))
	{
		Comment(L"�f�o�C�X�̍쐬�Ɏ��s", L"device.cpp/Device::CreateDevice");
		return hr;
	}
	return hr;
}

/**
* @brief CommandQueue�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateCommandQueue()
{
	HRESULT hr = S_OK;
	D3D12_COMMAND_QUEUE_DESC command_queue_desc{};

	command_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	command_queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	hr = device->CreateCommandQueue(&command_queue_desc, IID_PPV_ARGS(&command_queue));
	if (FAILED(hr))
	{
		Comment(L"�R�}���h�L���[�̍쐬�Ɏ��s", L"device.cpp/Device::CreateCommandQueue");
		return hr;
	}

	fence_event = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
	if (fence_event == nullptr)
	{
		return E_FAIL;
	}
	hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&queue_fence));
	if (FAILED(hr))
	{
		Comment(L"�t�F���X�̍쐬�Ɏ��s", L"device.cpp/Device::CreateCommandQueue");
		return hr;
	}
	return hr;
}

/**
* @brief SwapChain�̍쐬
* @param hwnd �E�B���h�E�n���h��
* @return �����������ǂ���
*/
HRESULT Device::CreateSwapChain(HWND hwnd)
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
	swap_chain_desc.BufferDesc.Width = WINDOW_WIDTH;
	swap_chain_desc.BufferDesc.Height = WINDOW_HEIGHT;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.BufferCount = FrameNum;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = FPS;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;

	ComPtr<IDXGISwapChain> swap_chain_temp{};
	hr = factory->CreateSwapChain(command_queue.Get(), &swap_chain_desc, swap_chain_temp.GetAddressOf());
	if (FAILED(hr))
	{
		Comment(L"�X���b�v�`�F�C���̍쐬�Ɏ��s", L"device.cpp/Device::CreateSwapChain");
		return hr;
	}
	hr = swap_chain_temp->QueryInterface(swap_chain.GetAddressOf());
	if (FAILED(hr))
	{
		Comment(L"SwapChain�C���^�[�t�F�[�X���T�|�[�g���Ă��܂���", L"device.cpp/Device::CreateSwapChain");
		return hr;
	}
	//���݂̃o�b�N�o�b�t�@�̃C���f�b�N�X���擾
	rtv_index = swap_chain->GetCurrentBackBufferIndex();

	return hr;
}

/**
* @brief CommandAllocator�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateCommandAllocator()
{
	HRESULT hr = S_OK;
	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"�R�}���h�A���P�[�^�[�̍쐬�Ɏ��s", L"device.cpp/Device::CreateCommandAllocator");
		return hr;
	}
	return hr;
}

/**
* @brief CommandList�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateCommandList()
{
	HRESULT hr = S_OK;
	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator.Get(), nullptr, IID_PPV_ARGS(&command_list));
	if (FAILED(hr))
	{
		Comment(L"�R�}���h���X�g�̍쐬�Ɏ��s", L"device.cpp/Device::CreateCommandList");
		return hr;
	}
	hr = ExecuteCommand(command_list, command_allocator, nullptr);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief RootSignature�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateRootSignature()
{
	HRESULT hr = S_OK;
	D3D12_DESCRIPTOR_RANGE range[1]{};
	range[0].NumDescriptors = 1;
	range[0].BaseShaderRegister = 0;
	range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_ROOT_PARAMETER root_parameters[2]{};
	root_parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	root_parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	root_parameters[1].DescriptorTable.NumDescriptorRanges = 1;
	root_parameters[1].DescriptorTable.pDescriptorRanges = &range[0];

	D3D12_STATIC_SAMPLER_DESC sampler_desc{};
	sampler_desc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc.MipLODBias = 0.0f;
	sampler_desc.MaxAnisotropy = 16;
	sampler_desc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	sampler_desc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	sampler_desc.MinLOD = 0.0f;
	sampler_desc.MaxLOD = D3D12_FLOAT32_MAX;
	sampler_desc.ShaderRegister = 0;
	sampler_desc.RegisterSpace = 0;
	sampler_desc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	D3D12_ROOT_SIGNATURE_DESC	root_signature_desc{};
	root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	root_signature_desc.NumParameters = _countof(root_parameters);
	root_signature_desc.pParameters = root_parameters;
	root_signature_desc.NumStaticSamplers = 1;
	root_signature_desc.pStaticSamplers = &sampler_desc;

	ComPtr<ID3DBlob> blob{};
	hr = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &blob, nullptr);
	if (FAILED(hr))
	{
		Comment(L"���[�g�V�O�l�`���̃V���A���C�Y�Ɏ��s", L"device.cpp/Device::CreateRootSignature");
		return hr;
	}
	hr = device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&root_signature));
	if (FAILED(hr))
	{
		Comment(L"���[�g�V�O�l�`���̍쐬�Ɏ��s", L"device.cpp/Device::CreateRootSignature");
		return hr;
	}
	return hr;
}

/**
* @brief RenderTargetView�̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateRenderTargetView()
{
	HRESULT hr = S_OK;

	D3D12_DESCRIPTOR_HEAP_DESC heap_desc{};
	heap_desc.NumDescriptors = FrameNum;
	heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heap_desc.NodeMask = 0;
	hr = device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&dh_rtv));
	if (FAILED(hr))
	{
		Comment(L"RTV�p�f�X�N���v�^�q�[�v�̍쐬�Ɏ��s", L"device.cpp/Device::CreateRenderTargetView");
		return hr;
	}
	UINT size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	for (UINT i = 0; i < FrameNum; ++i)
	{
		hr = swap_chain->GetBuffer(i, IID_PPV_ARGS(&render_targets[i]));
		if (FAILED(hr))
		{
			Comment(L"�X���b�v�`�F�C������̃o�b�t�@�̎󂯎��Ɏ��s", L"device.cpp/Device::CreateRenderTargetView");
			return hr;
		}
		rtv_handle[i] = dh_rtv->GetCPUDescriptorHandleForHeapStart();
		rtv_handle[i].ptr += size * i;
		device->CreateRenderTargetView(render_targets[i].Get(), nullptr, rtv_handle[i]);

	}

	return hr;
}

/**
* @brief �f�v�X�X�e���V���̍쐬
* @return �����������ǂ���
*/
HRESULT Device::CreateDepthStencilBuffer()
{
	HRESULT hr = S_OK;

	D3D12_DESCRIPTOR_HEAP_DESC heap_desc{};
	heap_desc.NumDescriptors = 1;
	heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heap_desc.NodeMask = 0;
	hr = device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&dh_dsv));
	if (FAILED(hr))
	{
		Comment(L"DSV�p�f�X�N���v�^�q�[�v�̍쐬�Ɏ��s", L"device.cpp/Device::CreateDepthStencilBuffer");
		return hr;
	}

	D3D12_HEAP_PROPERTIES heap_properties{};
	heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resource_desc.Width = WINDOW_WIDTH;
	resource_desc.Height = WINDOW_HEIGHT;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 0;
	resource_desc.Format = DXGI_FORMAT_R32_TYPELESS;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;
	resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE clear_value{};
	clear_value.Format = DXGI_FORMAT_D32_FLOAT;
	clear_value.DepthStencil.Depth = 1.0f;
	clear_value.DepthStencil.Stencil = 0;

	hr = device->CreateCommittedResource(&heap_properties, D3D12_HEAP_FLAG_NONE,
		&resource_desc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clear_value, IID_PPV_ARGS(&depth_buffer));
	if (FAILED(hr))
	{
		Comment(L"DSV�p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s", L"device.cpp/Device::CreateDepthStencilBuffer");
		return hr;
	}

	D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc{};

	dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Format = DXGI_FORMAT_D32_FLOAT;
	dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsv_desc.Texture2D.MipSlice = 0;
	dsv_desc.Flags = D3D12_DSV_FLAG_NONE;

	dsv_handle = dh_dsv->GetCPUDescriptorHandleForHeapStart();
	device->CreateDepthStencilView(depth_buffer.Get(), &dsv_desc, dsv_handle);

	return hr;
}

/**
* @brief �������Ƃ�
* @return �����������ǂ���
*/
HRESULT Device::WaitForPreviousFrame()
{
	HRESULT hr = S_OK;
	++frames;
	const UINT64 fence = frames;
	hr = command_queue->Signal(queue_fence.Get(), fence);
	if (FAILED(hr))
	{
		Comment(L"fence�̍X�V�Ɏ��s", L"device.cpp/Device::WaitForPreviousFrame");
		return hr;
	}
	if (queue_fence->GetCompletedValue() < fence)
	{
		hr = queue_fence->SetEventOnCompletion(fence, fence_event);
		if (FAILED(hr))
		{
			Comment(L"�C�x���g�̎w��Ɏ��s", L"device.cpp/Device::WaitForPreviousFrame");
			return hr;
		}
		WaitForSingleObject(fence_event, INFINITE);
	}
	return hr;
}

/**
* @brief �f�o�C�X�̃Q�b�^
* @return �f�o�C�X
*/
ComPtr<ID3D12Device>& Device::GetDevice()
{
	return (device);
}

/**
* @brief �R�}���h���X�g�̃Q�b�^
* @return �R�}���h���X�g
*/
ComPtr<ID3D12GraphicsCommandList>& Device::GetCommandList()
{
	return (command_list);
}

/**
* @brief ���[�g�V�O�l�`���̃Q�b�^
* @return ���[�g�V�O�l�`��
*/
ComPtr<ID3D12RootSignature>& Device::GetRootSignature()
{
	return (root_signature);
}