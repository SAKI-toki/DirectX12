/**
* @file tan.h
* @brief コンパイル時tan
* @author 石山 悠
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
	* @brief コンパイル時tan
	* @param x ラジアン角
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
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	* @param x int型のラジアン角
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double tan(T x)
	{
		return saki::tan(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_TAN_2019_01_05