/**
* @file gamepad_input.h
* @brief ゲームパッドのインプットクラスの宣言
* @author 石山　悠
* @date 2018/12/20
*/
#pragma once
#include "../../common/d3d12.h"
#include <saki/singleton.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")


/**
* @brief ボタンのenum class
* @details デフォルトの長いマクロを使わず、こっちで管理する
*/
enum class BUTTON {
	A, B, X, Y, START, BACK,
	DPAD_UP, DPAD_DOWN, DPAD_RIGHT, DPAD_LEFT,
	STICK_R, STICK_L, R1, L1, BUTTON_END
};

/**
* @brief ゲームパッドのインプットクラス
*/
class GamepadInput :public saki::singleton<GamepadInput>
{
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
	} controller[CONTROLLER_NUM];

	//ボタンの状態
	bool old_button[CONTROLLER_NUM][14];
	bool current_button[CONTROLLER_NUM][14];
	//コントローラーのバイブレーションの力
	float right_power[CONTROLLER_NUM]{};
	float left_power[CONTROLLER_NUM]{};

	/**
	* @brief 引数1と引数2の論理積が引数2と完全に一致しているときのみを返す
	* @param u1,u2 比べる対象
	* @return 引数2と等しいかどうか
	*/
	template<typename U1, typename U2>
	bool perfect_and(const U1 u1, const U2 u2)const
	{
		return (u1&u2) == u2;
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
public:
	GamepadInput();
	void Update();
	void Vibration(size_t index, float, float);

	///--ゲッタ--
	/**
	* @brief ボタンを押したかどうか
	* @param index コントローラーの番号
	* @param b 判定するボタン
	*/
	bool GetButtonDown(size_t index, BUTTON b)const
	{
		if (!index_check(index))return false;
		return controller[index].bConnected &&
			!old_button[index][static_cast<int>(b)] && current_button[index][static_cast<int>(b)];
	};
	/**
	* @brief ボタンを押しているかどうか
	* @param index コントローラーの番号
	* @param b 判定するボタン
	*/
	bool GetButton(size_t index, BUTTON b)const
	{
		if (!index_check(index))return false;
		return controller[index].bConnected&&
			current_button[index][static_cast<int>(b)];
	};
	/**
	* @brief ボタンを離したかどうか
	* @param index コントローラーの番号
	* @param b 判定するボタン
	*/
	bool GetButtonUp(size_t index, BUTTON b)const
	{
		if (!index_check(index))return false;
		return controller[index].bConnected&&
			old_button[index][static_cast<int>(b)] && !current_button[index][static_cast<int>(b)];
	};

	/**
	* @brief トリガーの状態を返す
	* @param index コントローラーの番号
	* @param right 判定するのが右かどうか
	*/
	float GetTrigger(size_t index, const bool right)const
	{
		if (!index_check(index))return 0;
		//つながっていなかったら0を返す
		if (!controller[index].bConnected) { return 0; }
		auto trigger = (right ? controller[index].state.Gamepad.bRightTrigger : controller[index].state.Gamepad.bLeftTrigger) / 255.0f;

		if (trigger > TRIGGER_DEAD_ZONE)
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
	float GetStick(size_t index, const bool right, const bool x)const
	{
		if (!index_check(index))return 0;
		//つながっていなかったら0を返す
		if (!controller[index].bConnected) { return 0; }
		auto stick = (right ?
			(x ? controller[index].state.Gamepad.sThumbRX : controller[index].state.Gamepad.sThumbRY) :
			x ? controller[index].state.Gamepad.sThumbLX : controller[index].state.Gamepad.sThumbLY) / 32767.0f;

		if (std::abs(stick) > (right ? STICK_DEAD_ZONE : STICK_DEAD_ZONE))
		{
			return stick;
		}
		return 0;
	}
};
