/**
* @file pow.h
* @brief —İæ‚ğ‹‚ß‚éŠÖ”
* @author ÎR —I
* @date 2019/01/07
*/
#pragma once
#ifndef SAKI_MATH_POW_2019_01_07
#define SAKI_MATH_POW_2019_01_07
#include <cstddef>
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/signbit.h>
#include <saki/math/log.h>
#include <saki/math/exp.h>
#include <saki/math/fmod.h>
#include <saki/math/abs.h>
#include <saki/math/is_odd_even.h>
#include <saki/math/isinf.h>
#include <saki/math/details/pow_n.h>

namespace saki
{
	/**
	* @brief ƒRƒ“ƒpƒCƒ‹—İæ
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T pow(T x, T y)
	{
		if (x == 1 || y == 0)return static_cast<T>(1);
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
		if (x == 0)
		{
			if (y < 0)
			{
				if (saki::is_odd(y))
				{
					return saki::copysign(std::numeric_limits<T>::infinity(), x);
				}
				else
				{
					return std::numeric_limits<T>::infinity();
				}
			}
			else
			{
				if (saki::is_odd(y))
				{
					return x;
				}
				else
				{
					return static_cast<T>(0);
				}
			}
		}
		if (x == -1 &&
			(saki::isinf(y)))return static_cast<T>(1);
		if (y == -std::numeric_limits<T>::infinity())
		{
			if (saki::abs(x) < 1)return std::numeric_limits<T>::infinity();
			else return static_cast<T>(0);
		}
		if (y == std::numeric_limits<T>::infinity())
		{
			if (saki::abs(x) > 1)return std::numeric_limits<T>::infinity();
			else return static_cast<T>(0);
		}
		if (x == -std::numeric_limits<T>::infinity())
		{
			if (saki::is_odd(y))
			{
				return (y < 0) ? static_cast<T>(-0) : -std::numeric_limits<T>::infinity();
			}
			else
			{
				return (y < 0) ? static_cast<T>(0) : std::numeric_limits<T>::infinity();
			}
		}
		if (x == std::numeric_limits<T>::infinity())
		{
			return(y < 0) ? static_cast<T>(0) : std::numeric_limits<T>::infinity();
		}
		if (x < 0 && saki::fmod(y, 1) != 0)return -std::numeric_limits<T>::quiet_NaN();

		//¬”“_‚È‚µ‚Ìê‡
		if (saki::fmod(y, 1) == 0)
		{
			return saki::details::pow_n(x, static_cast<int>(y));
		}

		//ˆ—
		if (x < 0)
		{
			if (saki::is_odd(y))
			{
				return -saki::exp(y * saki::log(-x));
			}
			else
			{
				return saki::exp(y * saki::log(-x));
			}
		}
		else
		{
			return saki::exp(y * saki::log(x));
		}
	}
	/**
	* @brief ˆø”‚ªintŒ^‚Ìê‡‚ÉA–ß‚è’l‚ğdoubleŒ^‚É‚·‚é‚½‚ß‚Ì‚à‚Ì
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double pow(T x, T y)
	{
		return saki::pow(static_cast<double>(x), static_cast<double>(y));
	}
	/**
	* @brief Œ^‚ğ‚»‚ë‚¦‚é
	*/
	template<typename T1,typename T2>
	constexpr auto pow(T1 x, T2 y)
	{
		return saki::pow(static_cast<decltype(x * y)>(x), static_cast<decltype(x * y)>(y));
	}
}
#endif //SAKI_MATH_POW_2019_01_07