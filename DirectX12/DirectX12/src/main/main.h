/**
* @file main.h
* @brief ���C���N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include <saki/singleton.h>
#include <string>
#include <memory>

/**
* @brief ���C���N���X
*/
class Main :public saki::singleton<Main>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Main();
	~Main()noexcept;
	bool InitWindow(HINSTANCE hInst, int nCmdShow);
	void MessageLoop();
	HWND GetHwnd();
};