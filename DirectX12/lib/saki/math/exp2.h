/**
* @file exp2.h
* @brief コンパイル時exp2
* @author 石山 悠
* @date 2019/01/10
*/
#pragma once
#ifndef SAKI_MATH_EXP2_2019_01_10
#define SAKI_MATH_EXP2_2019_01_10
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/exp.h>
#include <saki/math/log.h>

namespace saki
{
	/**
	* @brief コンパイル時exp2
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T exp2(T x)
	{
		if (saki::isnan(x) || x == std::numeric_limits<T>::infinity())return x;
		if (x == -std::numeric_limits<T>::infinity())return 0;
		if (x == 0)return static_cast<T>(1);

		return saki::exp(x * saki::log(2));
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double exp2(T x)
	{
		return saki::exp2(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_EXP2_2019_01_10