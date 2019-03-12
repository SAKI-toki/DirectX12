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
#include <string>

class Main :public saki::singleton<Main>
{
	//�A�v����
	const std::wstring APP_NAME{ L"Game" };
	//�E�B���h�E�n���h��
	HWND hwnd;
	//�C���X�^���X�n���h��
	HINSTANCE hinst;
	HRESULT Update();
	HRESULT Render();
public:
	bool InitWindow(HINSTANCE hInst, int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void MessageLoop();
	HWND GetHwnd();
};