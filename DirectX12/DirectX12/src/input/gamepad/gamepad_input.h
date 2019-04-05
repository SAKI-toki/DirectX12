/**
* @file gamepad_input.h
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/12/20
*/
#pragma once
#include <saki/singleton.h>
#include <memory>


/**
* @brief �{�^����enum class
* @details �f�t�H���g�̒����}�N�����g�킸�A�������ŊǗ�����
*/
enum class BUTTON {
	A, B, X, Y, START, BACK,
	DPAD_UP, DPAD_DOWN, DPAD_RIGHT, DPAD_LEFT,
	STICK_R, STICK_L, R1, L1, BUTTON_END
};

/**
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X
*/
class GamepadInput :public saki::singleton<GamepadInput>
{
	class Impl;
	std::unique_ptr<Impl>  pimpl;
	
public:
	GamepadInput();
	~GamepadInput()noexcept;
	void Update();
	void Vibration(size_t index, float left, float right);

	bool GetButtonDown(size_t index, BUTTON b)const;
	bool GetButton(size_t index, BUTTON b)const;
	bool GetButtonUp(size_t index, BUTTON b)const;
	float GetTrigger(size_t index, const bool right)const;
	float GetStick(size_t index, const bool right, const bool x)const;
};
