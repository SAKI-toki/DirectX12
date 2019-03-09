/**
* @file exp.h
* @brief コンパイル時exp
* @author 石山 悠
* @date 2019/01/06
*/
#pragma once
#ifndef SAKI_MATH_EXP_2019_01_06
#define SAKI_MATH_EXP_2019_01_06
#include <cstddef>
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/abs.h>
#include <saki/math/factorial.h>
#include <saki/math/isnan.h>
#include <saki/math/details/pow_n.h>
#include <saki/math/is_odd_even.h>

namespace saki
{
	/**
	* @brief コンパイル時exp
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T exp(T x)
	{
		if (saki::isnan(x) || x == std::numeric_limits<T>::infinity())return x;
		if (x == -std::numeric_limits<T>::infinity())return 0;
		if (x == 0)return static_cast<T>(1);

		bool minus = false;
		if (x <= -1)
		{
			minus = true;
			x *= -1;
		}
		size_t ad = 1;
		while (x > 2)
		{
			ad *= 2;
			x /= 2;
		}
		T sum = 1;
		size_t n = 1;
		while (n <= saki::factorial_limits<T>::limit)
		{
			sum += saki::details::pow_n(x, n) / saki::factorial<T>(n);
			++n;
		}
		return saki::details::pow_n(
			((minus) ? (1 / sum) : (sum)), 
			ad);
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double exp(T x)
	{
		return saki::exp(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_EXP_2019_01_06