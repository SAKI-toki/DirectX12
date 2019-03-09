/**
* @file keyboard_input.cpp
* @brief �L�[�{�[�h�̃C���v�b�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/12/20
*/
#include "keyboard_input.h"
#include "../../common/message_box.h"

/**
* @brief �L�[�{�[�h�̏�����
* @param hWnd �E�B���h�E�n���h��
* @return ����ɏ������������ǂ���
*/
HRESULT KeyboardInput::KeyboardInit(HWND hWnd)
{
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		Comment(L"DirectInput�̍쐬�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		Comment(L"�f�o�C�X�̍쐬�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		Comment(L"�f�[�^�t�H�[�}�b�g�̃Z�b�g�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		Comment(L"�������x���̃Z�b�g�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	int i;
	for (i = 0; i < 0; ++i) {
		current_diks[i] = 0;
	}
	return S_OK;
}

/**
* @brief �L�[�{�[�h�̍X�V
* @return ����ɍX�V�������ǂ���
*/
HRESULT KeyboardInput::Update()
{
	if (FAILED(pKeyDevice->Acquire()))
	{
		Comment(L"�f�o�C�X�̎擾�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}
	BYTE temp_diks[256];
	if (FAILED(pKeyDevice->GetDeviceState(sizeof(temp_diks), &temp_diks)))
	{
		Comment(L"�f�o�C�X���̎擾�Ɏ��s", L"keyboard_input.cpp");
		return E_FAIL;
	}

	int i;
	for (i = 0; i < 256; ++i)
	{
		old_diks[i] = current_diks[i];
		current_diks[i] = temp_diks[i];
	}
	return S_OK;
}

/**
* @brief �L�[�{�[�h�̔j��
*/
void KeyboardInput::Destroy()
{
	// �L�[�{�[�h�f�o�C�X�ւ̃A�N�Z�X���J��
	if (pKeyDevice)
		pKeyDevice->Unacquire();

	// �L�[�{�[�h�f�o�C�X�J��
	if (pKeyDevice)pKeyDevice->Release();
	pKeyDevice = NULL;
	// DirectInput�I�u�W�F�N�g�J��
	if (pDinput)pDinput->Release();
	pDinput = NULL;
}

/**
* @brief �w�肳�ꂽ�L�[�������Ă��邩�ǂ���
* @param key �L�[�ԍ�
* return �L�[�������Ă��邩�ǂ���
*/
bool KeyboardInput::GetKey(int key)
{
	return static_cast<bool>(current_diks[key] & 0x80);
}
/**
* @brief �w�肳�ꂽ�L�[�����������ǂ���
* @param key �L�[�ԍ�
* return �L�[�����������ǂ���
*/
bool KeyboardInput::GetKeyDown(int key)
{
	return static_cast<bool>(current_diks[key] & 0x80) && !static_cast<bool>(old_diks[key] & 0x80);
}
/**
* @brief �w�肳�ꂽ�L�[�𗣂������ǂ���
* @param key �L�[�ԍ�
* return �L�[�𗣂������ǂ���
*/
bool KeyboardInput::GetKeyUp(int key)
{
	return !static_cast<bool>(current_diks[key] & 0x80) && static_cast<bool>(old_diks[key] & 0x80);
}