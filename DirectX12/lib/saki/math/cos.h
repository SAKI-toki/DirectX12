/**
* @file cos.h
* @brief �R���p�C����cos
* @author �ΎR �I
* @date 2019/01/05
*/
#pragma once
#ifndef SAKI_MATH_COS_2019_01_05
#define SAKI_MATH_COS_2019_01_05
#include <cstddef>
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/factorial.h>
#include <saki/math/pi.h>
#include <saki/math/pow.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief �R���p�C����cos
	* @param x ���W�A���p
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T cos(T x)
	{
		//NaN
		if (saki::isnan(x))return x;
		//inf
		if (saki::isinf(x))
		{
			return -std::numeric_limits<T>::quiet_NaN();
		}
		//-PI��x��PI�͈̔͂Ɏ��߂�
		while (x > saki::PI<T>)x -= saki::PI<T> * 2;
		while (x < -saki::PI<T>)x += saki::PI<T> * 2;

		T sum = 0;
		size_t n = 0;
		while (n <= saki::factorial_limits<T>::limit / 2)
		{
			sum += static_cast<T>(((n % 2 == 0) ? 1 : -1) *
				saki::pow<T>(x, 2 * n) /
				saki::factorial<T>(2 * n));
			++n;
		}
		return sum;
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	* @param x int�^�̃��W�A���p
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double cos(T x)
	{
		return saki::cos(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_COS_2019_01_05