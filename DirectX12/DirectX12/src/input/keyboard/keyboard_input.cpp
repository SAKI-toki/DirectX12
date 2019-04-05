/**
* @file keyboard_input.cpp
* @brief キーボードのインプットクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/12/20
*/
#include "keyboard_input.h"
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include "../../common/message_box.h"

/**
* @brief キーボードのpimplイディオム
*/
class KeyboardInput::Impl
{
public:
	//各デバイス
	LPDIRECTINPUT8 pDinput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//キーの状態
	BYTE old_diks[256]{};
	BYTE current_diks[256]{};

	void Destroy();
};

#pragma region public

/**
* @brief キーボードのコンストラクタ
*/
KeyboardInput::KeyboardInput() :
	pimpl(new Impl{})
{}

/**
* @brief キーボードのデストラクタ
*/
KeyboardInput::~KeyboardInput()
{
	pimpl->Destroy();
}

/**
* @brief キーボードの初期化
* @param hWnd ウィンドウハンドラ
* @return 正常に初期化したかどうか
*/
HRESULT KeyboardInput::KeyboardInit(HWND hWnd)
{
	HRESULT hr = S_OK;
	hr = DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, IID_IDirectInput8,
		reinterpret_cast<void**>(&pimpl->pDinput), nullptr);
	if (FAILED(hr))
	{
		Comment(L"DirectInputの作成に失敗",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	hr = pimpl->pDinput->CreateDevice(GUID_SysKeyboard, &pimpl->pKeyDevice, nullptr);
	if (FAILED(hr))
	{
		Comment(L"デバイスの作成に失敗",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	hr = pimpl->pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		Comment(L"データフォーマットのセットに失敗",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	hr = pimpl->pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hr))
	{
		Comment(L"協調レベルのセットに失敗",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	for (int i = 0; i < 256; ++i)
	{
		pimpl->current_diks[i] = 0;
	}
	return hr;
}

/**
* @brief キーボードの更新
* @return 正常に更新したかどうか
*/
HRESULT KeyboardInput::Update()
{
	HRESULT hr = S_OK;
	hr = pimpl->pKeyDevice->Acquire();
	if (FAILED(hr))
	{
		Comment(L"デバイスの取得に失敗",
			L"keyboard_input.cpp/KeyboardInput::Update");
		return hr;
	}
	BYTE temp_diks[256];
	hr = pimpl->pKeyDevice->GetDeviceState(sizeof(temp_diks), &temp_diks);
	if (FAILED(hr))
	{
		Comment(L"デバイス情報の取得に失敗",
			L"keyboard_input.cpp/KeyboardInput::Update");
		return hr;
	}

	int i;
	for (i = 0; i < 256; ++i)
	{
		pimpl->old_diks[i] = pimpl->current_diks[i];
		pimpl->current_diks[i] = temp_diks[i];
	}
	return hr;
}

/**
* @brief 指定されたキーを押しているかどうか
* @param key キー番号
* return キーを押しているかどうか
*/
bool KeyboardInput::GetKey(int key)
{
	return static_cast<bool>(pimpl->current_diks[key] & 0x80);
}

/**
* @brief 指定されたキーを押したかどうか
* @param key キー番号
* return キーを押したかどうか
*/
bool KeyboardInput::GetKeyDown(int key)
{
	return static_cast<bool>(pimpl->current_diks[key] & 0x80) &&
		!static_cast<bool>(pimpl->old_diks[key] & 0x80);
}

/**
* @brief 指定されたキーを離したかどうか
* @param key キー番号
* return キーを離したかどうか
*/
bool KeyboardInput::GetKeyUp(int key)
{
	return !static_cast<bool>(pimpl->current_diks[key] & 0x80) &&
		static_cast<bool>(pimpl->old_diks[key] & 0x80);
}

#pragma endregion

#pragma region pimpl

/**
* @brief キーボードの破棄
*/
void KeyboardInput::Impl::Destroy()
{
	// キーボードデバイスへのアクセス権開放
	if (pKeyDevice)
		pKeyDevice->Unacquire();

	// キーボードデバイス開放
	if (pKeyDevice)pKeyDevice->Release();
	pKeyDevice = nullptr;
	// DirectInputオブジェクト開放
	if (pDinput)pDinput->Release();
	pDinput = nullptr;
}

#pragma endregion
