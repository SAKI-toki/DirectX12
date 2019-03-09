/**
* @file clock.h
* @brief ���Ԃ𑪂�N���X
* @author �ΎR �I
* @date 2018/12/04
*/
#pragma once
#ifndef SAKI_CLOCK_CLOCK_2018_12_04
#define SAKI_CLOCK_CLOCK_2018_12_04
#include <chrono>
namespace saki
{
	/**
	* @brief ���Ԃ𑪂�N���X
	*/
	class clock
	{
		std::chrono::system_clock::time_point start_time;//�J�n����
	public:
		/**
		* @brief �R���X�g���N�^
		*/
		clock() :start_time(std::chrono::system_clock::now()) {}
	public:
		enum class DURATION { HOUR, MINUTE, SECOND, MILLISECOND, MICROSECOND, NANOSECOND, NONE };
		/**
		* @brief �J�n���Ԃ̃Z�b�g
		*/
		void start()
		{
			start_time = std::chrono::system_clock::now();
		}
		/**
		* @brief �J�n���Ԃ��Z�b�g���Ă���̎��Ԃ�Ԃ�
		* @param duration �ǂ̒P�ʂŕԂ���
		* return ����
		*/
		template<typename T = double>
		T end(DURATION duration = DURATION::MILLISECOND)
		{
			auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::system_clock::now() - start_time).count();
			switch (duration)
			{
			case DURATION::MICROSECOND: //�}�C�N���b
			{
				return static_cast<T>(elapsed_time * 0.001);
			}
			case DURATION::MILLISECOND: //�~���b
			{
				return static_cast<T>(elapsed_time * 0.001 * 0.001);
			}
			case DURATION::SECOND: //�b
			{
				return static_cast<T>(elapsed_time * 0.001 * 0.001 * 0.001);
			}
			case DURATION::MINUTE: //��
			{
				return static_cast<T>(elapsed_time * 0.001 * 0.001 * 0.001 / 60);
			}
			case DURATION::HOUR: //����
			{
				return static_cast<T>(elapsed_time * 0.001 * 0.001 * 0.001 / 60 / 60);
			}
			default: //�i�m�b
			{
				return static_cast<T>(elapsed_time);
			}
			}
		}
		/**
		* @brief �J�n���Ԃ��Z�b�g���Ă���̎��Ԃ�Ԃ��A��������܂����Ԃ��X�^�[�g����
		* @param duration �ǂ̒P�ʂŕԂ���
		* return ����
		*/
		template<typename T = double>
		T end_and_start(DURATION duration = DURATION::MILLISECOND)
		{
			auto t = end<T>(duration);
			start();
			return t;
		}
	};
}
#endif //SAKI_CLOCK_CLOCK_2018_12_04