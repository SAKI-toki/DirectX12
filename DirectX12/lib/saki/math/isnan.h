/**
* @file isnan.h
* @brief Not a Number���ǂ������肷��֐�
* @author �ΎR �I
* @date 2019/01/02
*/
#pragma once
#ifndef SAKI_MATH_ISNAN_2019_01_02
#define SAKI_MATH_ISNAN_2019_01_02
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief Not a Number���ǂ�������
	* @param x ���肷��l
	* @return NaN���ǂ���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
	constexpr bool isnan(T x)
	{
		return !(x == x);
	}
	/**
	* @brief Not a Number���ǂ�������
	* @param x ���肷��l
	* @details floating_point�ȊO��false
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<!std::is_floating_point_v<T>> = nullptr>
		constexpr bool isnan(T)
	{
		return false;
	}
}
#endif //SAKI_MATH_ISNAN_2019_01_02