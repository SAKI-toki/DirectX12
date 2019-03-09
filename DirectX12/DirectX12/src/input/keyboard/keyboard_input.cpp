/**
* @file keyboard_input.cpp
* @brief キーボードのインプットクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/12/20
*/
#include "keyboard_input.h"
#include "../../common/message_box.h"

/**
* @brief キーボードの初期化
* @param hWnd ウィンドウハンドラ
* @return 正常に初期化したかどうか
*/
HRESULT KeyboardInput::KeyboardInit(HWND hWnd)
{
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		Comment(L"DirectInputの作成に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		Comment(L"デバイスの作成に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		Comment(L"データフォーマットのセットに失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		Comment(L"協調レベルのセットに失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	int i;
	for (i = 0; i < 0; ++i) {
		current_diks[i] = 0;
	}
	return S_OK;
}

/**
* @brief キーボードの更新
* @return 正常に更新したかどうか
*/
HRESULT KeyboardInput::Update()
{
	if (FAILED(pKeyDevice->Acquire()))
	{
		Comment(L"デバイスの取得に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}
	BYTE temp_diks[256];
	if (FAILED(pKeyDevice->GetDeviceState(sizeof(temp_diks), &temp_diks)))
	{
		Comment(L"デバイス情報の取得に失敗", L"keyboard_input.cpp");
		return E_FAIL;
	}

	int i;
	for (i = 0; i < 256; ++i)
	{
		old_diks[i] = current_diks[i];
		current_diks[i] = temp_diks[i];
	}
	return S_OK;
}

/**
* @brief キーボードの破棄
*/
void KeyboardInput::Destroy()
{
	// キーボードデバイスへのアクセス権開放
	if (pKeyDevice)
		pKeyDevice->Unacquire();

	// キーボードデバイス開放
	if (pKeyDevice)pKeyDevice->Release();
	pKeyDevice = NULL;
	// DirectInputオブジェクト開放
	if (pDinput)pDinput->Release();
	pDinput = NULL;
}

/**
* @brief 指定されたキーを押しているかどうか
* @param key キー番号
* return キーを押しているかどうか
*/
bool KeyboardInput::GetKey(int key)
{
	return static_cast<bool>(current_diks[key] & 0x80);
}
/**
* @brief 指定されたキーを押したかどうか
* @param key キー番号
* return キーを押したかどうか
*/
bool KeyboardInput::GetKeyDown(int key)
{
	return static_cast<bool>(current_diks[key] & 0x80) && !static_cast<bool>(old_diks[key] & 0x80);
}
/**
* @brief 指定されたキーを離したかどうか
* @param key キー番号
* return キーを離したかどうか
*/
bool KeyboardInput::GetKeyUp(int key)
{
	return !static_cast<bool>(current_diks[key] & 0x80) && static_cast<bool>(old_diks[key] & 0x80);
}