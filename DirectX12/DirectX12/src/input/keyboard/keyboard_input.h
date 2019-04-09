/**
* @file keyboard_input.h
* @brief キーボードのインプットクラスの宣言
* @author 石山　悠
* @date 2018/12/20
*/
#pragma once
#include "../../common/d3d12.h"
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <saki/singleton.h>

/**
* @brief キーボードのインプットクラス
*/
class KeyboardInput :public saki::singleton<KeyboardInput>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
	
public:
	KeyboardInput();
	~KeyboardInput();
	HRESULT KeyboardInit(HWND hwnd);
	HRESULT Update();
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
};