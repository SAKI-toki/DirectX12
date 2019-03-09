/**
* @file fmod.h
* @brief �R���p�C����float,double��]
* @author �ΎR �I
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
	* @brief �R���p�C����float,double��]
	* @param x �����鐔
	* @param y ���鐔
	* @return ��]
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

		//����
		return static_cast<T>(x - static_cast<int64_t>(x / y) * y);
	}
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr T fmod(T x, T y)
	{
		return (x % y);
	}
	/**
	* @brief �^���Ⴄ�ꍇ�͂��낦��
	*/
	template<typename T1, typename T2>
	constexpr auto fmod(T1 x, T2 y)
		->decltype(x * y)
	{
		return saki::fmod(static_cast<decltype(x * y)>(x), static_cast<decltype(x * y)>(y));
	}
}
#endif //SAKI_MATH_FMOD_2019_01_02