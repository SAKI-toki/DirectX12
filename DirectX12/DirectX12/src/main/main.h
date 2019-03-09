/**
* @file main.h
* @brief ���C�����Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../common/window_size.h"
#include "../common/d3d12.h"
#include <saki/singleton.h>

class Main :public saki::singleton<Main>
{
	//�A�v����
	static constexpr WCHAR* APP_NAME = L"Game";
	//�E�B���h�E�n���h��
	HWND hwnd;
	//�C���X�^���X�n���h��
	HINSTANCE hinst;
	HRESULT Update();
	HRESULT Render();
public:
	bool InitWindow(HINSTANCE, int);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void MessageLoop();
	HWND GetHwnd();
};