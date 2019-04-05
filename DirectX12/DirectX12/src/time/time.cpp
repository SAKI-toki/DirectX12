/**
* @file time.cpp
* @brief ���Ԃ��Ǘ�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2019/03/05
*/
#include "time.h"
#include "../text_ui/text_ui.h"
#include <saki/clock.h>
#include <string>
#include <sstream>
#include <iomanip>

/**
* @brief ���Ԃ��Ǘ�����N���X��pimpl�C�f�B�I��
*/
class Time::Impl
{
public:
	//���Ԃ𑪂�
	saki::clock my_clock;
	//�o�ߎ���(�X�P�[�����f)
	float elapsed_time = 0.0f;
	//�o�ߎ���(�X�P�[�����f�Ȃ�)
	float elapsed_time_not_scale = 0.0f;
	//���Ԃ̃X�P�[��
	float time_scale = 1.0f;
};

#pragma region public

/**
* @brief ���Ԃ��Ǘ�����N���X�̃R���X�g���N�^
*/
Time::Time() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
Time::~Time()noexcept = default;

/**
* @brief ���Ԃ̍X�V�A���t���[���Ă�
*/
void Time::UpdateTime()
{
	pimpl->elapsed_time_not_scale = pimpl->my_clock.end_and_start<float>(saki::clock::DURATION::SECOND);
	pimpl->elapsed_time = pimpl->elapsed_time_not_scale * pimpl->time_scale;
}

/**
* @brief �X�P�[���𔽉f�����o�ߎ��Ԃ̎擾
* @return �o�ߎ���(�X�P�[���𔽉f)
*/
float Time::GetElapsedTime()
{
	return pimpl->elapsed_time;
}

/**
* @brief �X�P�[���𔽉f���Ȃ��o�ߎ��Ԃ̎擾
* @return �o�ߎ���(�X�P�[���𔽉f���Ȃ�)
*/
float Time::GetElapsedTimeNotScale()
{
	return pimpl->elapsed_time_not_scale;
}

/**
* @brief ���Ԃ̃X�P�[���̃Z�b�^
* @param scale �Z�b�g����X�P�[��
*/
void Time::SetTimeScale(float scale)
{
	pimpl->time_scale = scale;
}

/**
* @brief ���Ԃ̃X�P�[���̃Q�b�^
* @return ���Ԃ̃X�P�[��
*/
float Time::GetTimeScale()
{
	return pimpl->time_scale;
}

/**
* @brief Fps�̕`��
* @param pos �ʒu
*/
void Time::DrawFps(const Vec2& pos)
{
	//���������Ŋ��������邽�߂ɐÓI�ɂ���
	static UINT update_count = 0;
	static constexpr double update_delay = 1.0;
	static double sum_time = 0;
	static std::wstring fps{ L"FPS:60.00" };
	sum_time += Time::getinstance()->GetElapsedTimeNotScale();
	++update_count;
	//��莞�Ԍo�߂�����X�V
	if (sum_time > update_delay)
	{
		std::wstringstream wss;
		wss << "FPS:" << std::fixed << std::setprecision(2) << 1.0f / (sum_time / update_count);
		fps.clear();
		wss >> fps;
		update_count = 0;
		sum_time = 0;
	}
	TextUi::getinstance()->DrawString(fps, pos);
}

#pragma endregion