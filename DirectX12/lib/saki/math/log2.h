/**
* @file log2.h
* @brief コンパイル時log2
* @author 石山 悠
* @date 2019/01/13
*/
#pragma once
#ifndef SAKI_MATH_LOG2_2019_01_13
#define SAKI_MATH_LOG2_2019_01_13
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/log.h>

namespace saki
{
	/**
	* @brief コンパイル時log2
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T log2(T x)
	{
		if (saki::isnan(x) || x == std::numeric_limits<T>::infinity())return x;
		if (x == -std::numeric_limits<T>::infinity() || x < 0)return -std::numeric_limits<T>::quiet_NaN();
		if (x == 0)return -std::numeric_limits<T>::infinity();
		if (x == 1)return 0;

		return saki::log(x) / saki::log(2);
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double log2(T x)
	{
		return saki::log2(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_LOG2_2019_01_13