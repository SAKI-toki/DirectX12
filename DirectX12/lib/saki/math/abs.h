/**
* @file abs.h
* @brief �R���p�C������Βl
* @author �ΎR �I
* @date 2019/01/19
*/
#pragma once
#ifndef SAKI_MATH_ABS_2019_01_19
#define SAKI_MATH_ABS_2019_01_19
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>

namespace saki
{
	/**
	* @brief �R���p�C������Βl
	* @param x ��Βl�����߂�l
	* @details ��������
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<!std::is_unsigned_v<T>> = nullptr>
	constexpr T abs(T x)
	{
		if (saki::isnan(x))return x;
		return x < 0 ? -x : x;
	}
	/**
	* @brief �R���p�C������Βl
	* @param x ��Βl�����߂�l
	* @details �����Ȃ�
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_unsigned_v<T>> = nullptr>
	constexpr T abs(T x)
	{
		return x;
	}
}
#endif //SAKI_MATH_ABS_2019_01_19