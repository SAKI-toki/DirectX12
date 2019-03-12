/**
* @file execute_command_list.cpp
* @brief 実行用コマンドリストクラスの関数定義
* @author 石山　悠
* @date 2019/03/11
*/
#include "execute_command_list.h"
#include "../../device/device.h"
#include "../../common/message_box.h"
#include "../Bundle/bundle.h"

#pragma region public

/**
* @brief 実行用コマンドリストの初期化
* @return 成功したかどうか
*/
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

/**
* @brief 描画開始
* @return 成功したかどうか
*/
HRESULT ExecuteCommandList::BeginScene()
{
	HRESULT hr = S_OK;

	//描画開始時に必要なものをセットする
	hr = Device::getinstance()->BeginSceneSet(command_list);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief 描画
* @return 成功したかどうか
*/
HRESULT ExecuteCommandList::Execute()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->ExecuteCommand(command_list, command_allocator, pipeline.Get());
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief コマンドリストのゲッタ
* @return コマンドリスト
*/
ComPtr<ID3D12GraphicsCommandList>& ExecuteCommandList::GetCommandList()
{
	return (command_list);
}

/**
* @brief パイプラインステートのゲッタ
* @return パイプラインステート
*/
ComPtr<ID3D12PipelineState>& ExecuteCommandList::GetPipeline()
{
	return (pipeline);
}

#pragma endregion

#pragma region private

/**
* @brief 実行用のコマンドアロケーターの作成
* @return 成功したかどうか
*/
HRESULT ExecuteCommandList::CreateCommandAllocator()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, 
			IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"コマンドアロケーターの作成に失敗",
			L"command_list.cpp/CommandList::CreateCommandAllocator");
		return hr;
	}

	return hr;
}

/**
* @brief 実行用のコマンドリストの作成
* @return 成功したかどうか
*/
HRESULT ExecuteCommandList::CreateCommandList()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
			command_allocator.Get(), pipeline.Get(), 
			IID_PPV_ARGS(&command_list));
	if (FAILED(hr))
	{
		Comment(L"コマンドリストの作成に失敗",
			L"command_list.cpp/CommandList::CreateCommandList");
		return hr;
	}
	hr = Execute();
	if (FAILED(hr))return hr;

	return hr;
}

#pragma endregion