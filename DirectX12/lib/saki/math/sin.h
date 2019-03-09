/**
* @file sin.h
* @brief コンパイル時sin
* @author 石山 悠
* @date 2019/01/03
*/
#pragma once
#ifndef SAKI_MATH_SIN_2019_01_03
#define SAKI_MATH_SIN_2019_01_03
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/factorial.h>
#include <saki/math/pi.h>
#include <saki/math/pow.h>
#include <saki/math/isnan.h>
#include <saki/math/cos.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief コンパイル時sin
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T sin(T x)
	{
		//NaN
		if (saki::isnan(x) || x == 0)return x;
		//inf
		if (saki::isinf(x))
		{
			return -std::numeric_limits<T>::quiet_NaN();
		}

		return -saki::cos(x + saki::PI_HALF<T>);
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double sin(T x)
	{
		return saki::sin(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_SIN_2019_01_03