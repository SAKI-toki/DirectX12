/**
* @file keyboard_input.h
* @brief キーボードのインプットクラスの宣言
* @author 石山　悠
* @date 2018/12/20
*/
#pragma once
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <saki/singleton.h>

/**
* @brief キーボードのインプットクラス
*/
class KeyboardInput :public saki::singleton<KeyboardInput>
{
	//各デバイス
	LPDIRECTINPUT8 pDinput;
	LPDIRECTINPUTDEVICE8 pKeyDevice;

	//キーの状態
	BYTE old_diks[256];
	BYTE current_diks[256];

	void Destroy();
public:
	HRESULT KeyboardInit(HWND hwnd);
	HRESULT Update();
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	/**
	* @brief デストラクタ
	*/
	~KeyboardInput()
	{
		Destroy();
	}
};