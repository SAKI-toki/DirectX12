/**
* @file is_odd_even.h
* @brief Šï”‚ª‚Ç‚¤‚©A‹ô”‚©‚Ç‚¤‚©”»’è‚·‚éŠÖ”
* @author ÎR —I
* @date 2019/01/07
*/
#pragma once
#ifndef SAKI_MATH_IS_ODD_EVEN_2019_01_07
#define SAKI_MATH_IS_ODD_EVEN_2019_01_07
#include <limits>
#include <saki/math/fmod.h>
#include <saki/math/isinf.h>
#include <saki/math/isnan.h>

namespace saki
{
	/**
	* @brief Šï”‚ª‚Ç‚¤‚©”»’è‚·‚éŠÖ”
	*/
	template<typename T>
	constexpr bool is_odd(T x)
	{
		if (saki::isnan(x))return false;
		return saki::isinf(x) ||
			saki::fmod(((x > 0) ? x : -x), 2) == static_cast<T>(1);
	}
	/**
	* @brief ‹ô”‚ª‚Ç‚¤‚©”»’è‚·‚éŠÖ”
	*/
	template<typename T>
	constexpr bool is_even(T x)
	{
		if (saki::isnan(x))return false;
		return x == saki::isinf(x) ||
			saki::fmod(((x > 0) ? x : -x), 2) == static_cast<T>(0);
	}
}
#endif //SAKI_MATH_IS_ODD_EVEN_2019_01_07