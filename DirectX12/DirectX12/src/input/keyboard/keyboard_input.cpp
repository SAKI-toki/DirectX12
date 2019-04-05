/**
* @file keyboard_input.cpp
* @brief �L�[�{�[�h�̃C���v�b�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/12/20
*/
#include "keyboard_input.h"
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include "../../common/message_box.h"

/**
* @brief �L�[�{�[�h��pimpl�C�f�B�I��
*/
class KeyboardInput::Impl
{
public:
	//�e�f�o�C�X
	LPDIRECTINPUT8 pDinput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//�L�[�̏��
	BYTE old_diks[256]{};
	BYTE current_diks[256]{};

	void Destroy();
};

#pragma region public

/**
* @brief �L�[�{�[�h�̃R���X�g���N�^
*/
KeyboardInput::KeyboardInput() :
	pimpl(new Impl{})
{}

/**
* @brief �L�[�{�[�h�̃f�X�g���N�^
*/
KeyboardInput::~KeyboardInput()
{
	pimpl->Destroy();
}

/**
* @brief �L�[�{�[�h�̏�����
* @param hWnd �E�B���h�E�n���h��
* @return ����ɏ������������ǂ���
*/
HRESULT KeyboardInput::KeyboardInit(HWND hWnd)
{
	HRESULT hr = S_OK;
	hr = DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, IID_IDirectInput8,
		reinterpret_cast<void**>(&pimpl->pDinput), nullptr);
	if (FAILED(hr))
	{
		Comment(L"DirectInput�̍쐬�Ɏ��s",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	hr = pimpl->pDinput->CreateDevice(GUID_SysKeyboard, &pimpl->pKeyDevice, nullptr);
	if (FAILED(hr))
	{
		Comment(L"�f�o�C�X�̍쐬�Ɏ��s",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	hr = pimpl->pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		Comment(L"�f�[�^�t�H�[�}�b�g�̃Z�b�g�Ɏ��s",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	hr = pimpl->pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(hr))
	{
		Comment(L"�������x���̃Z�b�g�Ɏ��s",
			L"keyboard_input.cpp/KeyboardInput::KeyboardInit");
		return hr;
	}
	for (int i = 0; i < 256; ++i)
	{
		pimpl->current_diks[i] = 0;
	}
	return hr;
}

/**
* @brief �L�[�{�[�h�̍X�V
* @return ����ɍX�V�������ǂ���
*/
HRESULT KeyboardInput::Update()
{
	HRESULT hr = S_OK;
	hr = pimpl->pKeyDevice->Acquire();
	if (FAILED(hr))
	{
		Comment(L"�f�o�C�X�̎擾�Ɏ��s",
			L"keyboard_input.cpp/KeyboardInput::Update");
		return hr;
	}
	BYTE temp_diks[256];
	hr = pimpl->pKeyDevice->GetDeviceState(sizeof(temp_diks), &temp_diks);
	if (FAILED(hr))
	{
		Comment(L"�f�o�C�X���̎擾�Ɏ��s",
			L"keyboard_input.cpp/KeyboardInput::Update");
		return hr;
	}

	int i;
	for (i = 0; i < 256; ++i)
	{
		pimpl->old_diks[i] = pimpl->current_diks[i];
		pimpl->current_diks[i] = temp_diks[i];
	}
	return hr;
}

/**
* @brief �w�肳�ꂽ�L�[�������Ă��邩�ǂ���
* @param key �L�[�ԍ�
* return �L�[�������Ă��邩�ǂ���
*/
bool KeyboardInput::GetKey(int key)
{
	return static_cast<bool>(pimpl->current_diks[key] & 0x80);
}

/**
* @brief �w�肳�ꂽ�L�[�����������ǂ���
* @param key �L�[�ԍ�
* return �L�[�����������ǂ���
*/
bool KeyboardInput::GetKeyDown(int key)
{
	return static_cast<bool>(pimpl->current_diks[key] & 0x80) &&
		!static_cast<bool>(pimpl->old_diks[key] & 0x80);
}

/**
* @brief �w�肳�ꂽ�L�[�𗣂������ǂ���
* @param key �L�[�ԍ�
* return �L�[�𗣂������ǂ���
*/
bool KeyboardInput::GetKeyUp(int key)
{
	return !static_cast<bool>(pimpl->current_diks[key] & 0x80) &&
		static_cast<bool>(pimpl->old_diks[key] & 0x80);
}

#pragma endregion

#pragma region pimpl

/**
* @brief �L�[�{�[�h�̔j��
*/
void KeyboardInput::Impl::Destroy()
{
	// �L�[�{�[�h�f�o�C�X�ւ̃A�N�Z�X���J��
	if (pKeyDevice)
		pKeyDevice->Unacquire();

	// �L�[�{�[�h�f�o�C�X�J��
	if (pKeyDevice)pKeyDevice->Release();
	pKeyDevice = nullptr;
	// DirectInput�I�u�W�F�N�g�J��
	if (pDinput)pDinput->Release();
	pDinput = nullptr;
}

#pragma endregion
