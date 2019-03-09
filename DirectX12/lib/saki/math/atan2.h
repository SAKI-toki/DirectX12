/**
* @file atan2.h
* @brief コンパイル時atan2
* @author 石山 悠
* @date 2019/01/06
*/
#pragma once
#ifndef SAKI_MATH_ATAN2_2019_01_06
#define SAKI_MATH_ATAN2_2019_01_06
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/signbit.h>
#include <saki/math/copysign.h>
#include <saki/math/atan.h>
#include <saki/math/pi.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief コンパイル時atan2
	* @param y,x 辺の長さ
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T atan2(T y, T x)
	{
		if (saki::isnan(x))
		{
			if (saki::isnan(y))
			{
				return saki::signbit(x) && saki::signbit(y) ?
					-std::numeric_limits<T>::quiet_NaN() :
					std::numeric_limits<T>::quiet_NaN();
			}
			else
			{
				return x;
			}
		}
		if (saki::isnan(y))return static_cast<T>(y);
		if (y == 0)
		{
			return (x < 0) ? saki::PI<T> : 0;
		}
		if (x == 0)
		{
			return saki::copysign(saki::PI_HALF<T>, y);
		}
		if (saki::isinf(y))
		{
			return (x == std::numeric_limits<T>::infinity()) ?
				saki::copysign(saki::PI_QUARTER<T>, y) :
				(x == -std::numeric_limits<T>::infinity()) ?
				saki::copysign(saki::PI_QUARTER<T> * 3, y) :
				saki::copysign(saki::PI_HALF<T>, y);
		}
		if (x == std::numeric_limits<T>::infinity())
		{
			return saki::copysign<T>(0, y);
		}
		if (x == -std::numeric_limits<T>::infinity())
		{
			return saki::copysign(saki::PI<T>, y);
		}

		//0<x
		if (0 < x)
		{
			return saki::atan(y / x);
		}
		//x<0,0<y
		else if (0 < y)
		{
			return saki::atan(y / x) + saki::PI<T>;
		}
		//x<0,y<0
		return saki::atan(y / x) - saki::PI<T>;
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double atan2(T y, T x)
	{
		return saki::atan2(static_cast<double>(y), static_cast<double>(x));
	}
	/**
	* @brief 型をそろえる
	*/
	template<typename T1, typename T2>
	constexpr auto atan2(T1 y, T2 x)
	{
		return saki::atan2(static_cast<decltype(y * x)>(y), static_cast<decltype(y * x)>(x));
	}
}
#endif //SAKI_MATH_ATAN2_2019_01_06