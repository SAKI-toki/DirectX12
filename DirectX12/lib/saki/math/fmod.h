/**
* @file fmod.h
* @brief コンパイル時float,double剰余
* @author 石山 悠
* @date 2019/01/02
*/
#pragma once
#ifndef SAKI_MATH_FMOD_2019_01_02
#define SAKI_MATH_FMOD_2019_01_02
#include <cstddef>
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/signbit.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief コンパイル時float,double剰余
	* @param x 割られる数
	* @param y 割る数
	* @return 剰余
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
	constexpr T fmod(T x, T y)
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
		if (saki::isinf(x) || y == 0)
		{
			return -std::numeric_limits<T>::quiet_NaN();
		}
		if (x == 0)return static_cast<T>(x);
		if (saki::isinf(y))
		{
			return static_cast<T>(x);
		}

		//処理
		return static_cast<T>(x - static_cast<int64_t>(x / y) * y);
	}
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr T fmod(T x, T y)
	{
		return (x % y);
	}
	/**
	* @brief 型が違う場合はそろえる
	*/
	template<typename T1, typename T2>
	constexpr auto fmod(T1 x, T2 y)
		->decltype(x * y)
	{
		return saki::fmod(static_cast<decltype(x * y)>(x), static_cast<decltype(x * y)>(y));
	}
}
#endif //SAKI_MATH_FMOD_2019_01_02