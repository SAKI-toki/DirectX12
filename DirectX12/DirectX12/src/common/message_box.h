/**
* @file message_box.h
* @brief ���b�Z�[�W�{�b�N�X�̊֐����`
* @author �ΎR�@�I
* @date 2019/03/06
*/
#pragma once
#define NOMINMAX//min,max�̃}�N���֐��̒�`���������
#include <Windows.h>
/**
* @brief ���b�Z�[�W�{�b�N�X���g���₷������
*/
template<typename T1, typename T2 = WCHAR*>
void Comment(const T1& t1, const T2& t2 = L"")
{
	MessageBox(NULL, t1, t2, MB_OK);
}