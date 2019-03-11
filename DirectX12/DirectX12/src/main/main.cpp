/**
* @file main.cpp
* @brief �G���g���[
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "main.h"
#include "../device/device.h"
#include "../camera/camera.h"
#include "../input/gamepad/gamepad_input.h"
#include "../input/keyboard/keyboard_input.h"
#include "../time/time.h"
#include "../common/message_box.h"
#include "../scene/manager/scene_manager.h"

/**
* @brief �G���g���[�֐�
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
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
	Camera::getinstance()->Init();
	hr = SceneManager::getinstance()->Init();
	if (FAILED(hr))return 0;
	//���b�Z�[�W���[�v
	Main::getinstance()->MessageLoop();
	return 0;
}

/**
* @brief �E�B���h�E�̏�����
*/
bool Main::InitWindow(HINSTANCE hInst, int nCmdShow)
{
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hinst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = APP_NAME.c_str();
	if (!RegisterClassEx(&wcex))
	{
		Comment(L"�E�B���h�E�o�^�Ɏ��s", L"main.cpp/Main::InitWindow");
		return false;
	}

	hinst = hInst;
	hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, APP_NAME.c_str(), APP_NAME.c_str(),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hinst, 0);

	if (!hwnd)
	{
		Comment(L"�E�B���h�E�����Ɏ��s", L"main.cpp/Main::InitWindow");
		return false;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return true;
}

/**
* @brief �E�B���h�E�v���V�[�W��
*/
LRESULT CALLBACK Main::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

/**
* @brief ���b�Z�[�W���[�v
*/
void Main::MessageLoop()
{
	MSG msg{};
	HRESULT hr = S_OK;
	while (WM_QUIT != msg.message)
	{
		Time::getinstance()->UpdateTime();
		//fps�̕\��
#ifdef _DEBUG
		static UINT update_count = 0;
		if (++update_count > 100)
		{
			WCHAR fps[256];
			swprintf_s(fps, L"%4.3f", 1.0f / Time::getinstance()->GetElapsedTimeNotScale());
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)fps);
			update_count = 0;
		}
#endif

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) { break; }
		}
		//�X�V
		hr = Update();
		if (FAILED(hr))break;
		//�`��
		hr = Render();
		if (FAILED(hr))break;
	}
	UnregisterClass(APP_NAME.c_str(), 0);
	hwnd = 0;
}

/**
* @brief �E�B���h�E�n���h���̎擾
*/
HWND Main::GetHwnd()
{
	return hwnd;
}

/**
* @brief �S�̂̍X�V
*/
HRESULT Main::Update()
{
	HRESULT hr = S_OK;

	//�L�[�{�[�h�̍X�V
	hr = KeyboardInput::getinstance()->Update();
	if (FAILED(hr))hr;
	//�Q�[���p�b�h�̍X�V
	GamepadInput::getinstance()->Update();
	//�V�[���̍X�V
	hr = SceneManager::getinstance()->Update();
	if (FAILED(hr))hr;
	//�J�����̍X�V
	Camera::getinstance()->Update();

	return hr;
}

/**
* @brief �S�̂̕`��
*/
HRESULT Main::Render()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->BeginScene();
	if (FAILED(hr))return hr;
	//------�`��X�^�[�g-----//

	//�V�[���̕`��
	hr = SceneManager::getinstance()->Render();
	if (FAILED(hr))return hr;

	//------�`��G���h-------//
	hr = Device::getinstance()->EndScene();
	if (FAILED(hr))return hr;
	//Present
	hr = Device::getinstance()->Present();
	if (FAILED(hr))return hr;

	return hr;
}