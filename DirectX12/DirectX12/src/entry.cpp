/**
* @file entry.cpp
* @brief �G���g���[
* @author �ΎR�@�I
* @date 2019/04/5
*/
#include "common/d3d12.h"
#include "main/main.h"
#include "device/device.h"
#include "input/keyboard/keyboard_input.h"
#include "sound/manager/sound_manager.h"
#include "scene/manager/scene_manager.h"

/**
* @brief �G���g���[�֐�
*/
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int nCmdShow)
{
	HRESULT hr = S_OK;
	//�E�B���h�E����
	if (!Main::getinstance()->InitWindow(hInstance, nCmdShow))
	{
		return 0;
	}
	//�f�o�C�X�̏�����
	hr = Device::getinstance()->InitDevice(Main::getinstance()->GetHwnd());
	if (FAILED(hr))return 0;
	hr = KeyboardInput::getinstance()->KeyboardInit(Main::getinstance()->GetHwnd());
	if (FAILED(hr))return 0;
	hr = SoundManager::getinstance()->Init();
	if (FAILED(hr))return 0;
	hr = SceneManager::getinstance()->Init();
	if (FAILED(hr))return 0;
	//���b�Z�[�W���[�v
	Main::getinstance()->MessageLoop();
	return 0;
}