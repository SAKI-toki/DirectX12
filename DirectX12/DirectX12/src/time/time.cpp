/**
* @file time.cpp
* @brief ���Ԃ��Ǘ�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2019/03/05
*/
#include "time.h"

/**
* @brief ���Ԃ̍X�V�A���t���[���Ă�
*/
void Time::UpdateTime()
{
	elapsed_time = my_clock.end_and_start<float>(saki::clock::DURATION::SECOND);
}

/**
* @brief �X�P�[���𔽉f�����o�ߎ��Ԃ̎擾
* @return �o�ߎ���(�X�P�[���𔽉f)
*/
float Time::GetElapsedTime()
{
	return elapsed_time * time_scale;
}

/**
* @brief �X�P�[���𔽉f���Ȃ��o�ߎ��Ԃ̎擾
* @return �o�ߎ���(�X�P�[���𔽉f���Ȃ�)
*/
float Time::GetElapsedTimeNotScale()
{
	return elapsed_time;
}

/**
* @brief ���Ԃ̃X�P�[���̃Z�b�^
* @param scale �Z�b�g����X�P�[��
*/
void Time::SetTimeScale(float scale)
{
	time_scale = scale;
}

/**
* @brief ���Ԃ̃X�P�[���̃Q�b�^
* @return ���Ԃ̃X�P�[��
*/
float Time::GetTimeScale()
{
	return time_scale;
}