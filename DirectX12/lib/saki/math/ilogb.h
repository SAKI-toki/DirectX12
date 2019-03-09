/**
* @file ilogb.h
* @brief コンパイル時ilogb
* @author 石山 悠
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_MATH_ILOGB_2019_01_15
#define SAKI_MATH_ILOGB_2019_01_15
#include <type_traits>
#include <cmath>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/logb.h>

namespace saki
{
	/**
	* @brief コンパイル時ilogb
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr int ilogb(T x)
	{
		if (saki::isnan(x))return FP_ILOGBNAN;
		if (saki::isinf(x))return INT_MAX;
		if (x == 0)return FP_ILOGB0;
		return static_cast<int>(saki::logb(x));
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr int ilogb(T x)
	{
		return saki::ilogb(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_ILOGB_2019_01_15