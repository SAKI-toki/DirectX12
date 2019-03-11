#include "execute_command_list.h"
#include "../../device/device.h"
#include "../../common/message_box.h"

HRESULT ExecuteCommandList::Init()
{
	HRESULT hr = S_OK;

	hr = CreatePipeline();
	if (FAILED(hr))return hr;
	hr = CreateCommandAllocator();
	if (FAILED(hr))return hr;
	hr = CreateCommandList();
	if (FAILED(hr))return hr;

	return hr;
}

ComPtr<ID3D12GraphicsCommandList>& ExecuteCommandList::GetCommandList()
{
	return (command_list);
}

ComPtr<ID3D12PipelineState>& ExecuteCommandList::GetPipeline()
{
	return (pipeline);
}

HRESULT ExecuteCommandList::CreateCommandAllocator()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"コマンドアロケーターの作成に失敗",
			L"command_list.cpp/CommandList::CreateCommandAllocator");
		return hr;
	}

	return hr;
}

HRESULT ExecuteCommandList::CreateCommandList()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
			command_allocator.Get(), pipeline.Get(), IID_PPV_ARGS(&command_list));
	if (FAILED(hr))
	{
		Comment(L"コマンドリストの作成に失敗",
			L"command_list.cpp/CommandList::CreateCommandList");
		return hr;
	}
	hr = Device::getinstance()->ExecuteCommand(command_list, command_allocator, pipeline.Get());
	if (FAILED(hr))return hr;

	return hr;
}