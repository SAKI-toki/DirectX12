/**
* @file d3d12.h
* @brief directxに必要なヘッダをインクルード
* @author 石山　悠
* @date 2019/03/06
*/
#pragma once
#pragma warning(disable : 4005)
#define NOMINMAX//min,maxのマクロ関数の定義を回避する
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")