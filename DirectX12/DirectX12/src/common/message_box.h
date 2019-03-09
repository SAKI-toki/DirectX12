/**
* @file message_box.h
* @brief メッセージボックスの関数を定義
* @author 石山　悠
* @date 2019/03/06
*/
#pragma once
#define NOMINMAX//min,maxのマクロ関数の定義を回避する
#include <Windows.h>
/**
* @brief メッセージボックスを使いやすくした
*/
template<typename T1, typename T2 = WCHAR*>
void Comment(const T1& t1, const T2& t2 = L"")
{
	MessageBox(NULL, t1, t2, MB_OK);
}