/**
* @file asin.h
* @brief コンパイル時asin
* @author 石山 悠
* @date 2019/01/06
*/
#pragma once
#ifndef SAKI_MATH_ASIN_2019_01_06
#define SAKI_MATH_ASIN_2019_01_06
#include <cstddef>
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/abs.h>
#include <saki/math/factorial.h>
#include <saki/math/sqrt.h>
#include <saki/math/pow.h>
#include <saki/math/copysign.h>
#include <saki/math/pi.h>
#include <saki/math/isnan.h>

namespace saki
{
	/**
	* @brief コンパイル時asin
	* @param x 辺の比
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T asin(T x)
	{
		if (saki::isnan(x) || x == 0)return x;
		if (saki::abs(x) > 1)return -std::numeric_limits<T>::quiet_NaN();

		//精度向上のため値によって処理を分ける
		//0≦|x|≦1/√2
		if (saki::abs(x) <= (1.0 / saki::sqrt<T>(2)))
		{
			T sum = 0;
			size_t n = 0;
			while (n * 2 + 1 <= saki::factorial_limits<T>::limit)
			{
				sum += static_cast<T>(saki::factorial<T>(2 * n)*
					saki::pow(x, 2 * n + 1) /
					(saki::pow(4, n)*
						saki::pow(saki::factorial<T>(n), 2) *
						(2 * n + 1)));

				++n;
			}
			return sum;
		}
		//1/√2≦x<1
		else
		{
			return saki::copysign(saki::PI_HALF<T> -saki::asin<T>(saki::sqrt<T>(1 - x * x)), x);
		}
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	* @param x int型の比
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double asin(T x)
	{
		return saki::asin(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_ASIN_2019_01_06