/**
* @file cbrt.h
* @brief �R���p�C����cbrt
* @author �ΎR �I
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_MATH_CBRT_2019_01_08
#define SAKI_MATH_CBRT_2019_01_08
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/pow.h>

namespace saki
{
	/**
	* @brief �R���p�C����cbrt
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T cbrt(T x)
	{
		if (saki::isnan(x) || saki::isinf(x) || x == 0)return x;

		return static_cast<T>((x < 0) ? -saki::pow(-x, 1.0 / 3.0) : saki::pow(x, 1.0 / 3.0));
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double cbrt(T x)
	{
		return saki::cbrt(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_CBRT_2019_01_08