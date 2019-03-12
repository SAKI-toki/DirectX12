/**
* @file keyboard_input.h
* @brief �L�[�{�[�h�̃C���v�b�g�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/12/20
*/
#pragma once
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <saki/singleton.h>

/**
* @brief �L�[�{�[�h�̃C���v�b�g�N���X
*/
class KeyboardInput :public saki::singleton<KeyboardInput>
{
	//�e�f�o�C�X
	LPDIRECTINPUT8 pDinput;
	LPDIRECTINPUTDEVICE8 pKeyDevice;

	//�L�[�̏��
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
	* @brief �f�X�g���N�^
	*/
	~KeyboardInput()
	{
		Destroy();
	}
};