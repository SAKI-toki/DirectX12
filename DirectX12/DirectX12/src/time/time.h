/**
* @file time.h
* @brief ���Ԃ��Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/03/05
*/
#pragma once
#include "../common/alias.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief ���Ԃ��Ǘ�����N���X
*/
class Time :public saki::singleton<Time>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Time();
	~Time()noexcept;
	//���Ԃ̍X�V
	//���t���[���ĂԂ���
	void UpdateTime();
	//�X�P�[���𔽉f�����o�ߎ��Ԃ��擾
	float GetElapsedTime();
	//�X�P�[���𔽉f���Ȃ��o�ߎ��Ԃ��擾
	float GetElapsedTimeNotScale();
	//�X�P�[���̃Z�b�^
	void SetTimeScale(float);
	//�X�P�[���̃Q�b�^
	float GetTimeScale();
	//FPS�̕`��
	void DrawFps(const Vec2& pos);
};