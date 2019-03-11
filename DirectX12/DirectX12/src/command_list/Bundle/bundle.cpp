#include "bundle.h"
#include "../../device/device.h"
#include "../../common/message_box.h"

HRESULT Bundle::CreateCommandAllocator()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_BUNDLE, IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"コマンドアロケーターの作成に失敗",
			L"command_list.cpp/CommandList::CreateCommandAllocator");
		return hr;
	}

	return hr;
}

HRESULT Bundle::CreateCommandList()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_BUNDLE,
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