/**
* @file log10.h
* @brief コンパイル時log10
* @author 石山 悠
* @date 2019/01/12
*/
#pragma once
#ifndef SAKI_MATH_LOG10_2019_01_12
#define SAKI_MATH_LOG10_2019_01_12
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/log.h>

namespace saki
{
	/**
	* @brief コンパイル時log10
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T log10(T x)
	{
		if (saki::isnan(x) || x == std::numeric_limits<T>::infinity())return x;
		if (x == -std::numeric_limits<T>::infinity() || x < 0)return -std::numeric_limits<T>::quiet_NaN();
		if (x == 0)return -std::numeric_limits<T>::infinity();
		if (x == 1)return 0;

		return saki::log(x) / saki::log(10);
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double log10(T x)
	{
		return saki::log10(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_LOG10_2019_01_12