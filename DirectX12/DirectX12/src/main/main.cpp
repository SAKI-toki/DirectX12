/**
* @file main.cpp
* @brief エントリー
* @author 石山　悠
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
#include <sstream>
#include <iomanip>

/**
* @brief エントリー関数
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	HRESULT hr = S_OK;
	//ウィンドウ生成
	if (!Main::getinstance()->InitWindow(hInstance, nCmdShow))
	{
		return 0;
	}
	//デバイスの初期化
	hr = Device::getinstance()->InitDevice(Main::getinstance()->GetHwnd());
	if (FAILED(hr))return 0;
	hr = KeyboardInput::getinstance()->KeyboardInit(Main::getinstance()->GetHwnd());
	if (FAILED(hr))return 0;
	hr = SceneManager::getinstance()->Init();
	if (FAILED(hr))return 0;
	//メッセージループ
	Main::getinstance()->MessageLoop();
	return 0;
}

/**
* @brief ウィンドウの初期化
* @param hInst インスタンスハンドル
* @param nCmdShow コマンド
* @return 成功したかどうか
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
		Comment(L"ウィンドウ登録に失敗", L"main.cpp/Main::InitWindow");
		return false;
	}

	hinst = hInst;
	hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, APP_NAME.c_str(), APP_NAME.c_str(),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		0, 0, hinst, 0);

	if (!hwnd)
	{
		Comment(L"ウィンドウ生成に失敗", L"main.cpp/Main::InitWindow");
		return false;
	}
	//画面の中心の持ってくる
	{
		HWND hDeskWnd;
		RECT deskrc, rc;
		int x, y;

		hDeskWnd = GetDesktopWindow();
		GetWindowRect(hDeskWnd, (LPRECT)&deskrc);
		GetWindowRect(hwnd, (LPRECT)&rc);
		x = (deskrc.right - (rc.right - rc.left)) / 2;
		y = (deskrc.bottom - (rc.bottom - rc.top)) / 2;
		SetWindowPos(hwnd, HWND_TOP, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_SHOWWINDOW);
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return true;
}

/**
* @brief ウィンドウプロシージャ
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
* @brief メッセージループ
*/
void Main::MessageLoop()
{
	MSG msg{};
	HRESULT hr = S_OK;
	while (WM_QUIT != msg.message)
	{
		Time::getinstance()->UpdateTime();
#ifdef _DEBUG
		DisplayFps();
#endif

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) { break; }
		}
		//更新
		hr = Update();
		if (FAILED(hr))break;
		//描画
		hr = Render();
		if (FAILED(hr))break;
	}
	UnregisterClass(APP_NAME.c_str(), 0);
	hwnd = 0;
}

/**
* @brief ウィンドウハンドラの取得
* @return ウィンドウハンドラ
*/
HWND Main::GetHwnd()
{
	return hwnd;
}

/**
* @brief 全体の更新
* @return 成功したかどうか
*/
HRESULT Main::Update()
{
	HRESULT hr = S_OK;

	//キーボードの更新
	hr = KeyboardInput::getinstance()->Update();
	if (FAILED(hr))hr;
	//ゲームパッドの更新
	GamepadInput::getinstance()->Update();
	//シーンの更新
	hr = SceneManager::getinstance()->Update();
	if (FAILED(hr))hr;
	//カメラの更新
	Camera::getinstance()->Update();

	return hr;
}

/**
* @brief 全体の描画
* @return 成功したかどうか
*/
HRESULT Main::Render()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->BeginScene();
	if (FAILED(hr))return hr;
	//------描画スタート-----//

	//シーンの描画
	hr = SceneManager::getinstance()->Render();
	if (FAILED(hr))return hr;

	//------描画エンド-------//
	hr = Device::getinstance()->EndScene();
	if (FAILED(hr))return hr;
	//Present
	hr = Device::getinstance()->Present();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief fpsの表示
*/
void Main::DisplayFps()
{
	//ここだけで完結させるために静的にする
	static UINT update_count = 0;
	static constexpr double update_delay = 1.0;
	static double sum_time = 0;
	sum_time += Time::getinstance()->GetElapsedTimeNotScale();
	++update_count;
	//一定時間経過したら更新
	if (sum_time > update_delay)
	{
		std::wstringstream fps;
		fps << "FPS:" << std::fixed << std::setprecision(2) << 1.0f / (sum_time / update_count);
		//FPSをタイトルにする
		SendMessage(hwnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(fps.str().c_str()));
		update_count = 0;
		sum_time = 0;
	}
}