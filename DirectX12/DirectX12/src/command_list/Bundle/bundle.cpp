/**
* @file bundle.cpp
* @brief バンドルクラスの関数定義
* @author 石山　悠
* @date 2019/03/11
*/
#include "bundle.h"
#include "../../device/device.h"
#include "../../common/message_box.h"
#include "../Execute/execute_command_list.h"

/**
* @brief バンドルのpimplイディオム
*/
class Bundle::Impl
{
public:
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList(ComPtr<ID3D12PipelineState>& com_pipeline);
};

#pragma region public

/**
* @brief バンドルのコンストラクタ
*/
Bundle::Bundle() :
	pimpl(new Impl{})
{}

//デストラクタ、ムーブコンストラクタ、ムーブ代入演算子のデフォルト指定
Bundle::~Bundle()noexcept = default;
Bundle::Bundle(Bundle&&)noexcept = default;
Bundle& Bundle::operator=(Bundle&&)noexcept = default;

/**
* @brief バンドルの初期化
* @param pipeline バンドルのパイプライン
* @return 成功したかどうか
*/
HRESULT Bundle::Init(ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	hr = pimpl->CreateCommandAllocator();
	if (FAILED(hr))return hr;
	hr = pimpl->CreateCommandList(pipeline);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief バンドルをCloseする(コマンドを入れた後に一度だけ呼び出す)
* @return 成功したかどうか
*/
HRESULT Bundle::Close()
{
	HRESULT hr = S_OK;

	hr = pimpl->command_list->Close();
	if (FAILED(hr))
	{
		Comment(L"バンドル用のコマンドリストのCloseに失敗",
			L"bundle.cpp/Bundle::Close");
		return hr;
	}

	return hr;
}

/**
* @brief 実行用のコマンドリストのセット
* @param execute_command_list セットさせる実行用のコマンドリスト
* @return 成功したかどうか
*/
void Bundle::SetExecuteCommandList(ComPtr<ID3D12GraphicsCommandList>& execute_command_list)
{
	execute_command_list->ExecuteBundle(pimpl->command_list.Get());
}

/**
* @brief コマンドリストのゲッタ
* @return コマンドリスト
*/
ComPtr<ID3D12GraphicsCommandList>& Bundle::GetCommandList()
{
	return (pimpl->command_list);
}

#pragma endregion

#pragma region pimpl

/**
* @brief バンドルのコマンドアロケーターの作成
* @return 成功したかどうか
*/
HRESULT Bundle::Impl::CreateCommandAllocator()
{
	HRESULT hr = S_OK;

	//D3D12_COMMAND_LIST_TYPE_BUNDLEを指定する
	hr = Device::getinstance()->GetDevice()->
		CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_BUNDLE,
			IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"バンドル用のコマンドアロケーターの作成に失敗",
			L"bundle.cpp/Bundle::CreateCommandAllocator");
		return hr;
	}

	return hr;
}

/**
* @brief バンドルのコマンドリストの作成
* @return 成功したかどうか
*/
HRESULT Bundle::Impl::CreateCommandList(ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	//D3D12_COMMAND_LIST_TYPE_BUNDLEを指定する
	hr = Device::getinstance()->GetDevice()->
		CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_BUNDLE,
			command_allocator.Get(), pipeline.Get(), IID_PPV_ARGS(&command_list));
	if (FAILED(hr))
	{
		Comment(L"バンドル用のコマンドリストの作成に失敗",
			L"bundle.cpp/Bundle::CreateCommandList");
		return hr;
	}

	return hr;
}

#pragma endregion