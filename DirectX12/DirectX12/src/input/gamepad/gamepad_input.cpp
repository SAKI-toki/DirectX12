/**
* @file gamepad_input.cpp
* @brief �Q�[���p�b�h�̃C���v�b�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/12/20
*/
#include "gamepad_input.h"
#include "../../common/d3d12.h"
#include <Xinput.h>
#pragma comment(lib,"xinput.lib")

/**
* @brief �Q�[���p�b�h��pimpl�C�f�B�I��
*/
class GamepadInput::Impl
{
public:
	Impl();
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
	} controller[CONTROLLER_NUM]{};

	//�{�^���̏��
	bool old_button[CONTROLLER_NUM][14]{};
	bool current_button[CONTROLLER_NUM][14]{};
	//�R���g���[���[�̃o�C�u���[�V�����̗�
	float right_power[CONTROLLER_NUM]{};
	float left_power[CONTROLLER_NUM]{};

	/**
	* @brief ����1�ƈ���2�̘_���ς�����2�Ɗ��S�Ɉ�v���Ă���Ƃ��݂̂�Ԃ�
	* @param u1,u2 ��ׂ�Ώ�
	* @return ����2�Ɠ��������ǂ���
	*/
	bool perfect_and(const WORD u1, const WORD u2)const
	{
		return (u1 & u2) == u2;
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
};

#pragma region public

/**
* @brief �R���X�g���N�^�ŏ�����
*/
GamepadInput::GamepadInput() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
GamepadInput::~GamepadInput()noexcept = default;

/**
* @brief �Q�[���p�b�h�C���v�b�g�̍X�V
*/
void GamepadInput::Update()
{
	for (size_t n = 0; n < pimpl->CONTROLLER_NUM; ++n)
	{
		//�R���g���[���[�̏�Ԃ��擾
		auto dw_result = XInputGetState(0, &pimpl->controller[n].state);
		for (int i = 0; i < 14; ++i)
		{
			pimpl->old_button[n][i] = pimpl->current_button[i];
		}
		//�R���g���[���[�ڑ�
		if (dw_result == ERROR_SUCCESS)
		{
			pimpl->controller[n].bConnected = true;
			//�{�^���̍X�V
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
		//�R���g���[���[���ڑ�
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
* @brief �R���g���[���[�̐U��
* @param index �R���g���[���[�̔ԍ�
* @param left ���̃��[�^�[�̗�
* @param right �E�̃��[�^�[�̗�
*/
void GamepadInput::Vibration(size_t index, float left, float right)
{
	if (!pimpl->index_check(index))return;
	//���ڑ�
	if (!pimpl->controller[index].bConnected)return;
	//�͈͓��̐U���Ɏ��߂�
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
* @brief �{�^�������������ǂ���
* @param index �R���g���[���[�̔ԍ�
* @param b ���肷��{�^��
*/
bool GamepadInput::GetButtonDown(size_t index, BUTTON b)const
{
	if (!pimpl->index_check(index))return false;
	return pimpl->controller[index].bConnected &&
		!pimpl->old_button[index][static_cast<int>(b)] && 
		pimpl->current_button[index][static_cast<int>(b)];
};

/**
* @brief �{�^���������Ă��邩�ǂ���
* @param index �R���g���[���[�̔ԍ�
* @param b ���肷��{�^��
*/
bool GamepadInput::GetButton(size_t index, BUTTON b)const
{
	if (!pimpl->index_check(index))return false;
	return pimpl->controller[index].bConnected &&
		pimpl->current_button[index][static_cast<int>(b)];
};

/**
* @brief �{�^���𗣂������ǂ���
* @param index �R���g���[���[�̔ԍ�
* @param b ���肷��{�^��
*/
bool GamepadInput::GetButtonUp(size_t index, BUTTON b)const
{
	if (!pimpl->index_check(index))return false;

	return pimpl->controller[index].bConnected &&
		pimpl->old_button[index][static_cast<int>(b)] && 
		!pimpl->current_button[index][static_cast<int>(b)];
};

/**
* @brief �g���K�[�̏�Ԃ�Ԃ�
* @param index �R���g���[���[�̔ԍ�
* @param right ���肷��̂��E���ǂ���
*/
float GamepadInput::GetTrigger(size_t index, const bool right)const
{
	if (!pimpl->index_check(index))return 0;
	//�Ȃ����Ă��Ȃ�������0��Ԃ�
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
* @brief �X�e�B�b�N�̏�Ԃ�Ԃ�
* @param index �R���g���[���[�̔ԍ�
* @param right ���肷��̂��E���ǂ���
* @param right ���肷��̂�x���ǂ���
*/
float GamepadInput::GetStick(size_t index, const bool right, const bool x)const
{
	if (!pimpl->index_check(index))return 0;
	//�Ȃ����Ă��Ȃ�������0��Ԃ�
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