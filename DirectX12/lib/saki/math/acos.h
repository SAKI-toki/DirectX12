/**
* @file acos.h
* @brief �R���p�C����acos
* @author �ΎR �I
* @date 2019/01/06
*/
#pragma once
#ifndef SAKI_MATH_ACOS_2019_01_06
#define SAKI_MATH_ACOS_2019_01_06
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/abs.h>
#include <saki/math/isnan.h>
#include <saki/math/pi.h>
#include <saki/math/asin.h>

namespace saki
{
	/**
	* @brief �R���p�C����acos
	* @param x �ӂ̔�
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T acos(T x)
	{
		if (saki::isnan(x))return x;
		if (saki::abs(x) > 1)return -std::numeric_limits<T>::quiet_NaN();

		return saki::PI_HALF<T> -saki::asin(x);
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	* @param x int�^�̔�
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double acos(T x)
	{
		return saki::acos(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_ACOS_2019_01_06