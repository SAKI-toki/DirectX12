/**
* @file gamepad_input.cpp
* @brief ゲームパッドのインプットクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/12/20
*/
#include "gamepad_input.h"
#include "../../common/d3d12.h"
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")

/**
* @brief ゲームパッドのpimplイディオム
*/
class GamepadInput::Impl
{
public:
	Impl();
	//スティックのデッドゾーン
	static constexpr float STICK_DEAD_ZONE = 0.3f;
	//トリガーのデッドゾーン
	static constexpr float TRIGGER_DEAD_ZONE = 0.3f;
	//コントローラーの数
	static constexpr size_t CONTROLLER_NUM = 4;
	//コントローラー構造体
	struct CONTROLLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	} controller[CONTROLLER_NUM]{};

	//ボタンの状態
	bool old_button[CONTROLLER_NUM][14]{};
	bool current_button[CONTROLLER_NUM][14]{};
	//コントローラーのバイブレーションの力
	float right_power[CONTROLLER_NUM]{};
	float left_power[CONTROLLER_NUM]{};

	/**
	* @brief 引数1と引数2の論理積が引数2と完全に一致しているときのみを返す
	* @param u1,u2 比べる対象
	* @return 引数2と等しいかどうか
	*/
	bool perfect_and(const WORD u1, const WORD u2)const
	{
		return (u1 & u2) == u2;
	}
	/**
	* @brief コントローラーの番号が上限以下かどうか判定する
	* @param index コントローラーの番号
	* @return 上限に収まっているかどうか
	*/
	bool index_check(size_t index)const
	{
		return (index < CONTROLLER_NUM);
	}
};

#pragma region public

/**
* @brief コンストラクタで初期化
*/
GamepadInput::GamepadInput() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
GamepadInput::~GamepadInput()noexcept = default;

/**
* @brief ゲームパッドインプットの更新
*/
void GamepadInput::Update()
{
	for (size_t n = 0; n < pimpl->CONTROLLER_NUM; ++n)
	{
		//コントローラーの状態を取得
		auto dw_result = XInputGetState(0, &pimpl->controller[n].state);
		for (int i = 0; i < 14; ++i)
		{
			pimpl->old_button[n][i] = pimpl->current_button[i];
		}
		//コントローラー接続
		if (dw_result == ERROR_SUCCESS)
		{
			pimpl->controller[n].bConnected = true;
			//ボタンの更新
			{
				auto dw_buttons = pimpl->controller[n].state.Gamepad.wButtons;
				bool button[] = { pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_A),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_B),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_X),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_Y),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_START),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_BACK),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_UP) ,
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_DOWN),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_RIGHT),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_DPAD_LEFT),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_RIGHT_THUMB),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_LEFT_THUMB),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_RIGHT_SHOULDER),
									pimpl->perfect_and(dw_buttons,XINPUT_GAMEPAD_LEFT_SHOULDER) };

				for (int i = 0; i < 14; ++i)
				{
					pimpl->current_button[n][i] = button[i];
				}
			}
		}
		//コントローラー未接続
		else
		{
			pimpl->controller[n].bConnected = false;
			for (int i = 0; i < 14; ++i)
			{
				pimpl->current_button[n][i] = false;
			}
		}
	}
}

/**
* @brief コントローラーの振動
* @param index コントローラーの番号
* @param left 左のモーターの力
* @param right 右のモーターの力
*/
void GamepadInput::Vibration(size_t index, float left, float right)
{
	if (!pimpl->index_check(index))return;
	//未接続
	if (!pimpl->controller[index].bConnected)return;
	//範囲内の振動に収める
	{
		if (right < 0)right = 0;
		else if (right > 1.0f)right = 1.0f;
		if (left < 0)left = 0;
		else if (left > 1.0f)left = 1.0f;
	}
	pimpl->right_power[index] = right;
	pimpl->left_power[index] = left;
	XINPUT_VIBRATION vibration;
	vibration.wRightMotorSpeed = static_cast<WORD>(UINT16_MAX * pimpl->right_power[index]);
	vibration.wLeftMotorSpeed = static_cast<WORD>(UINT16_MAX * pimpl->left_power[index]);
	XInputSetState(static_cast<DWORD>(index), &vibration);
}

/**
* @brief ボタンを押したかどうか
* @param index コントローラーの番号
* @param b 判定するボタン
*/
bool GamepadInput::GetButtonDown(size_t index, BUTTON b)const
{
	if (!pimpl->index_check(index))return false;
	return pimpl->controller[index].bConnected &&
		!pimpl->old_button[index][static_cast<int>(b)] && 
		pimpl->current_button[index][static_cast<int>(b)];
};

/**
* @brief ボタンを押しているかどうか
* @param index コントローラーの番号
* @param b 判定するボタン
*/
bool GamepadInput::GetButton(size_t index, BUTTON b)const
{
	if (!pimpl->index_check(index))return false;
	return pimpl->controller[index].bConnected &&
		pimpl->current_button[index][static_cast<int>(b)];
};

/**
* @brief ボタンを離したかどうか
* @param index コントローラーの番号
* @param b 判定するボタン
*/
bool GamepadInput::GetButtonUp(size_t index, BUTTON b)const
{
	if (!pimpl->index_check(index))return false;

	return pimpl->controller[index].bConnected &&
		pimpl->old_button[index][static_cast<int>(b)] && 
		!pimpl->current_button[index][static_cast<int>(b)];
};

/**
* @brief トリガーの状態を返す
* @param index コントローラーの番号
* @param right 判定するのが右かどうか
*/
float GamepadInput::GetTrigger(size_t index, const bool right)const
{
	if (!pimpl->index_check(index))return 0;
	//つながっていなかったら0を返す
	if (!pimpl->controller[index].bConnected) { return 0; }
	auto trigger = (right ? 
		pimpl->controller[index].state.Gamepad.bRightTrigger : 
		pimpl->controller[index].state.Gamepad.bLeftTrigger) / 255.0f;

	if (trigger > pimpl->TRIGGER_DEAD_ZONE)
	{
		return trigger;
	}
	return 0;
};

/**
* @brief スティックの状態を返す
* @param index コントローラーの番号
* @param right 判定するのが右かどうか
* @param right 判定するのがxかどうか
*/
float GamepadInput::GetStick(size_t index, const bool right, const bool x)const
{
	if (!pimpl->index_check(index))return 0;
	//つながっていなかったら0を返す
	if (!pimpl->controller[index].bConnected) { return 0; }
	auto stick = (right ?
		(x ? 
			pimpl->controller[index].state.Gamepad.sThumbRX :
			pimpl->controller[index].state.Gamepad.sThumbRY) :
		x ?
		pimpl->controller[index].state.Gamepad.sThumbLX : 
		pimpl->controller[index].state.Gamepad.sThumbLY) / 32767.0f;

	if (std::abs(stick) > pimpl->STICK_DEAD_ZONE)
	{
		return stick;
	}
	return 0;
}

#pragma endregion

#pragma region pimpl

GamepadInput::Impl::Impl()
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

#pragma endregion