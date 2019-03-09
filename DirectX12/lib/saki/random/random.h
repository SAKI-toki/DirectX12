/**
* @file random.h
* @brief ���߂�ꂽ�͈͂Ń����_���Ȓl���擾����
* @author �ΎR �I
* @date 2018/11/26
*/
/*
���߂�ꂽ�͈͂Ń����_���Ȓl���擾����֐��ł�
*/
#pragma once
#ifndef SAKI_RANDOM_RANDOM_2018_11_26
#define SAKI_RANDOM_RANDOM_2018_11_26
#include <random>
#include <cassert> //for assert
namespace saki
{
	/**
	* @brief �ŏ��l�ƍő�l�������ɂƂ�A���̊Ԃ��烉���_���Ȓl��Ԃ�
	* @param random_min �ŏ��l
	* @param random_max �ő�l
	* @details �ő�l���܂ރ����_���Ȓl��Ԃ�
	*/
	template<typename T>
	T random(const T random_min, const T random_max)
	{
		assert(random_min <= random_max);
		std::random_device rd;
		std::mt19937 mt(rd());
		if constexpr(std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> rnd(random_min, random_max);
			return rnd(mt);
		}
		else
		{
			std::uniform_real_distribution<T> rnd(random_min, random_max);
			return rnd(mt);
		}
	}
}
#endif //SAKI_RANDOM_RANDOM_2018_11_26