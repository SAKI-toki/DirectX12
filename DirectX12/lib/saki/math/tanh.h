/**
* @file tanh.h
* @brief �R���p�C����tanh
* @author �ΎR �I
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_MATH_TANH_2019_01_08
#define SAKI_MATH_TANH_2019_01_08
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/copysign.h>
#include <saki/math/sinh.h>
#include <saki/math/cosh.h>

namespace saki
{
	/**
	* @brief �R���p�C����tanh
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T tanh(T x)
	{
		if (saki::isnan(x) || x == 0)return x;
		if (saki::isinf(x))return static_cast<T>(saki::copysign(1, x));

		return saki::sinh(x) / saki::cosh(x);
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double tanh(T x)
	{
		return saki::tanh(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_TANH_2019_01_08