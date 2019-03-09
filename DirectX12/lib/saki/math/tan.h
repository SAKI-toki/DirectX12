/**
* @file tan.h
* @brief �R���p�C����tan
* @author �ΎR �I
* @date 2019/01/05
*/
#pragma once
#ifndef SAKI_MATH_TAN_2019_01_05
#define SAKI_MATH_TAN_2019_01_05
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/sin.h>
#include <saki/math/cos.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief �R���p�C����tan
	* @param x ���W�A���p
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T tan(T x)
	{
		//NaN
		if (saki::isnan(x))return x;
		//inf
		if (saki::isinf(x))
		{
			return -std::numeric_limits<T>::quiet_NaN();
		}
		return saki::sin(x) / saki::cos(x);
	}

	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	* @param x int�^�̃��W�A���p
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double tan(T x)
	{
		return saki::tan(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_TAN_2019_01_05