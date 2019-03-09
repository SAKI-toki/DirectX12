/**
* @file time.h
* @brief ���Ԃ��Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/03/05
*/
#pragma once
#include <saki/clock.h>
#include <saki/singleton.h>

/**
* @brief ���Ԃ��Ǘ�����N���X
*/
class Time :public saki::singleton<Time>
{
	//���Ԃ𑪂�
	saki::clock my_clock;
	//�o�ߎ���
	float elapsed_time = 0.0f;
	//���Ԃ̃X�P�[��
	float time_scale = 1.0f;
public:
	//���Ԃ̍X�V
	//���t���[���ĂԂ���
	void UpdateTime();
	//�X�P�[���𔽉f�����o�ߎ��Ԃ��擾
	float GetElapsedTime();
	//�X�P�[���𔽉f���Ȃ��r�̎��Ԃ��擾
	float GetElapsedTimeNotScale();
	//�X�P�[���̃Z�b�^
	void SetTimeScale(float);
	//�X�P�[���̃Q�b�^
	float GetTimeScale();
};