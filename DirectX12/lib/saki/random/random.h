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
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
namespace saki
{
	/**
	* @brief �ŏ��l�ƍő�l�������ɂƂ�A���̊Ԃ��烉���_���Ȓl��Ԃ�
	* @param random_min �ŏ��l
	* @param random_max �ő�l
	* @details �ő�l���܂ރ����_���Ȓl��Ԃ�
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_arithmetic_v<T>> = nullptr>
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
	template<typename T1, typename T2,
		typename saki::enable_if_nullptr_t<
		std::is_arithmetic_v<T1>&&
		std::is_arithmetic_v<T2>> = nullptr>
	auto random(const T1 random_min, const T2 random_max)
	{
		using type = std::common_type_t<T1, T2>;
		return random(static_cast<type>(random_min), static_cast<type>(random_max));
	}
}
#endif //SAKI_RANDOM_RANDOM_2018_11_26