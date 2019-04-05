/**
* @file main.cpp
* @brief メインクラスのメンバ関数の定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "main.h"
#include "../device/device.h"
#include "../camera/camera.h"
#include "../input/gamepad/gamepad_input.h"
#include "../input/keyboard/keyboard_input.h"
#include "../scene/manager/scene_manager.h"
#include "../time/time.h"
#include "../common/message_box.h"
#include "../common/window_size.h"
#include <sstream>
#include <iomanip>

/**
* @brief メインのpimplイディオム
*/
class Main::Impl
{
public:
	//アプリ名
	const std::wstring application_name{ L"Game" };
	//ウィンドウハンドラ
	HWND hwnd{};
	//インスタンスハンドラ
	HINSTANCE hinst{};
	HRESULT Update();
	HRESULT Render();
	void DisplayFps();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#pragma region public

/**
* @brief メインクラスのコンストラクタ
*/
Main::Main() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
Main::~Main()noexcept = default;

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
	wcex.lpfnWndProc = pimpl->WndProc;
	wcex.hInstance = pimpl->hinst;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = pimpl->application_name.c_str();
	if (!RegisterClassEx(&wcex))
	{
		Comment(L"ウィンドウ登録に失敗", 
			L"main.cpp/Main::InitWindow");
		return false;
	}

	pimpl->hinst = hInst;
	pimpl->hwnd = CreateWindowEx(WS_EX_ACCEPTFILES,
		pimpl->application_name.c_str(), pimpl->application_name.c_str(),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		0, 0, pimpl->hinst, 0);

	if (!pimpl->hwnd)
	{
		Comment(L"ウィンドウ生成に失敗", 
			L"main.cpp/Main::InitWindow");
		return false;
	}
	//画面の中心の持ってくる
	{
		HWND hDeskWnd;
		RECT deskrc, rc;
		int x, y;

		hDeskWnd = GetDesktopWindow();
		GetWindowRect(hDeskWnd, (LPRECT)&deskrc);
		GetWindowRect(pimpl->hwnd, (LPRECT)&rc);
		x = (deskrc.right - (rc.right - rc.left)) / 2;
		y = (deskrc.bottom - (rc.bottom - rc.top)) / 2;
		SetWindowPos(pimpl->hwnd, HWND_TOP, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_SHOWWINDOW);
	}

	ShowWindow(pimpl->hwnd, nCmdShow);
	UpdateWindow(pimpl->hwnd);

	return true;
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
		pimpl->DisplayFps();
#endif

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) { break; }
		}
		//更新
		hr = pimpl->Update();
		if (FAILED(hr))break;
		//描画
		hr = pimpl->Render();
		if (FAILED(hr))break;
	}
	UnregisterClass(pimpl->application_name.c_str(), 0);
	pimpl->hwnd = 0;
}

/**
* @brief ウィンドウハンドラの取得
* @return ウィンドウハンドラ
*/
HWND Main::GetHwnd()
{
	return pimpl->hwnd;
}

#pragma endregion

#pragma region pimpl

/**
* @brief 全体の更新
* @return 成功したかどうか
*/
HRESULT Main::Impl::Update()
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
HRESULT Main::Impl::Render()
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
void Main::Impl::DisplayFps()
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

/**
* @brief ウィンドウプロシージャ
*/
LRESULT CALLBACK Main::Impl::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

#pragma endregion