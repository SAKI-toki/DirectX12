/**
* @file gamepad_input.cpp
* @brief ゲームパッドのインプットクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/12/20
*/
#include "gamepad_input.h"

/**
* @brief コンストラクタで初期化
*/
GamepadInput::GamepadInput()
{
	for (int i = 0; i < 14; ++i)
	{
		for (size_t j = 0; j < CONTROLLER_NUM; ++j)
		{
			old_button[j][i] = false;
			current_button[j][i] = false;
		}
	}
}

/**
* @brief ゲームパッドインプットの更新
*/
void GamepadInput::Update()
{
	for (size_t n = 0; n < CONTROLLER_NUM; ++n)
	{
		//コントローラーの状態を取得
		auto dw_result = XInputGetState(0, &controller[n].state);
		for (int i = 0; i < 14; ++i)
		{
			old_button[n][i] = current_button[i];
		}
		//コントローラー接続
		if (dw_result == ERROR_SUCCESS)
		{
			controller[n].bConnected = true;
			//ボタンの更新
			{
				auto dw_buttons = controller[n].state.Gamepad.wButtons;
				bool button[] = { perfect_and(dw_buttons,XINPUT_GAMEPAD_A),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_B),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_X),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_Y),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_START),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_BACK),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_UP) ,
									perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_DOWN),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_RIGHT),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_LEFT),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_RIGHT_THUMB),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_LEFT_THUMB),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_RIGHT_SHOULDER),
									perfect_and(dw_buttons,XINPUT_GAMEPAD_LEFT_SHOULDER) };

				for (int i = 0; i < 14; ++i)
				{
					current_button[n][i] = button[i];
				}
			}
		}
		//コントローラー未接続
		else
		{
			controller[n].bConnected = false;
			for (int i = 0; i < 14; ++i)
			{
				current_button[n][i] = false;
			}
		}
	}
}

/**
* @brief コントローラーの振動
* @param index コントローラーの番号
* @param right 右のモーターの力
* @param left 左のモーターの力
*/
void GamepadInput::Vibration(size_t index, float right, float left)
{
	if (!index_check(index))return;
	//未接続
	if (!controller[index].bConnected)return;
	//範囲内の振動に収める
	{
		if (right < 0)right = 0;
		else if (right > 1.0f)right = 1.0f;
		if (left < 0)left = 0;
		else if (left > 1.0f)left = 1.0f;
	}
	right_power[index] = right;
	left_power[index] = left;
	XINPUT_VIBRATION vibration;
	vibration.wRightMotorSpeed = static_cast<WORD>(UINT16_MAX * right_power[index]);
	vibration.wLeftMotorSpeed = static_cast<WORD>(UINT16_MAX * left_power[index]);
	XInputSetState(static_cast<DWORD>(index), &vibration);
}
