/**
* @file main.h
* @brief メインを管理するクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/window_size.h"
#include "../common/d3d12.h"
#include <saki/singleton.h>
#include <string>

class Main :public saki::singleton<Main>
{
	//アプリ名
	const std::wstring APP_NAME{ L"Game" };
	//ウィンドウハンドラ
	HWND hwnd;
	//インスタンスハンドラ
	HINSTANCE hinst;
	HRESULT Update();
	HRESULT Render();
public:
	bool InitWindow(HINSTANCE, int);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void MessageLoop();
	HWND GetHwnd();
};