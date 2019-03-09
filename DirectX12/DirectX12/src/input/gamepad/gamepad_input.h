/**
* @file gamepad_input.h
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/12/20
*/
#pragma once
#include "../../common/d3d12.h"
#include <saki/singleton.h>
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")


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
	//�X�e�B�b�N�̃f�b�h�]�[��
	static constexpr float STICK_DEAD_ZONE = 0.3f;
	//�g���K�[�̃f�b�h�]�[��
	static constexpr float TRIGGER_DEAD_ZONE = 0.3f;
	//�R���g���[���[�̐�
	static constexpr size_t CONTROLLER_NUM = 4;
	//�R���g���[���[�\����
	struct CONTROLLER_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	} controller[CONTROLLER_NUM];

	//�{�^���̏��
	bool old_button[CONTROLLER_NUM][14];
	bool current_button[CONTROLLER_NUM][14];
	//�R���g���[���[�̃o�C�u���[�V�����̗�
	float right_power[CONTROLLER_NUM]{};
	float left_power[CONTROLLER_NUM]{};

	/**
	* @brief ����1�ƈ���2�̘_���ς�����2�Ɗ��S�Ɉ�v���Ă���Ƃ��݂̂�Ԃ�
	* @param u1,u2 ��ׂ�Ώ�
	* @return ����2�Ɠ��������ǂ���
	*/
	template<typename U1, typename U2>
	bool perfect_and(const U1 u1, const U2 u2)const
	{
		return (u1&u2) == u2;
	}
	/**
	* @brief �R���g���[���[�̔ԍ�������ȉ����ǂ������肷��
	* @param index �R���g���[���[�̔ԍ�
	* @return ����Ɏ��܂��Ă��邩�ǂ���
	*/
	bool index_check(size_t index)const
	{
		return (index < CONTROLLER_NUM);
	}
public:
	GamepadInput();
	void Update();
	void Vibration(size_t index, float, float);

	///--�Q�b�^--
	/**
	* @brief �{�^�������������ǂ���
	* @param index �R���g���[���[�̔ԍ�
	* @param b ���肷��{�^��
	*/
	bool GetButtonDown(size_t index, BUTTON b)const
	{
		if (!index_check(index))return false;
		return controller[index].bConnected &&
			!old_button[index][static_cast<int>(b)] && current_button[index][static_cast<int>(b)];
	};
	/**
	* @brief �{�^���������Ă��邩�ǂ���
	* @param index �R���g���[���[�̔ԍ�
	* @param b ���肷��{�^��
	*/
	bool GetButton(size_t index, BUTTON b)const
	{
		if (!index_check(index))return false;
		return controller[index].bConnected&&
			current_button[index][static_cast<int>(b)];
	};
	/**
	* @brief �{�^���𗣂������ǂ���
	* @param index �R���g���[���[�̔ԍ�
	* @param b ���肷��{�^��
	*/
	bool GetButtonUp(size_t index, BUTTON b)const
	{
		if (!index_check(index))return false;
		return controller[index].bConnected&&
			old_button[index][static_cast<int>(b)] && !current_button[index][static_cast<int>(b)];
	};

	/**
	* @brief �g���K�[�̏�Ԃ�Ԃ�
	* @param index �R���g���[���[�̔ԍ�
	* @param right ���肷��̂��E���ǂ���
	*/
	float GetTrigger(size_t index, const bool right)const
	{
		if (!index_check(index))return 0;
		//�Ȃ����Ă��Ȃ�������0��Ԃ�
		if (!controller[index].bConnected) { return 0; }
		auto trigger = (right ? controller[index].state.Gamepad.bRightTrigger : controller[index].state.Gamepad.bLeftTrigger) / 255.0f;

		if (trigger > TRIGGER_DEAD_ZONE)
		{
			return trigger;
		}
		return 0;
	};

	/**
	* @brief �X�e�B�b�N�̏�Ԃ�Ԃ�
	* @param index �R���g���[���[�̔ԍ�
	* @param right ���肷��̂��E���ǂ���
	* @param right ���肷��̂�x���ǂ���
	*/
	float GetStick(size_t index, const bool right, const bool x)const
	{
		if (!index_check(index))return 0;
		//�Ȃ����Ă��Ȃ�������0��Ԃ�
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
