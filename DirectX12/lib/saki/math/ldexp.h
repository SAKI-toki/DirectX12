/**
* @file ldexp.h
* @brief コンパイル時ldexp
* @author 石山 悠
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_MATH_LDEXP_2019_01_15
#define SAKI_MATH_LDEXP_2019_01_15
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/details/pow_n.h>

namespace saki
{
	/**
	* @brief コンパイル時ldexp
	*/
	template<typename T, typename IntegerT,
		typename saki::enable_if_nullptr_t<std::is_integral_v<IntegerT>> = nullptr>
		constexpr T ldexp(T x, IntegerT exp)
	{
		if (saki::isnan(x) || saki::isinf(x) || x == 0 || exp == 0)return x;

		return x * saki::details::pow_n(static_cast<T>(2), exp);
	}
	/**
	* @brief 第二引数がint型じゃない場合に、int型にするためのもの
	*/
	template<typename T, typename IntegerT,
		typename saki::enable_if_nullptr_t<!std::is_integral_v<IntegerT>> = nullptr>
		constexpr T ldexp(T x, IntegerT exp)
	{
		return saki::ldexp(x, static_cast<int>(exp));
	}
}
#endif //SAKI_MATH_LDEXP_2019_01_15