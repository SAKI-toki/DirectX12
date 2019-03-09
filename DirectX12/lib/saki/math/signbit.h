/**
* @file signbit.h
* @brief •‰”‚©‚Ç‚¤‚©”»’è‚·‚éŠÖ”
* @author ÎR —I
* @date 2019/01/03
*/
#pragma once
#ifndef SAKI_MATH_SIGNBIT_2019_01_03
#define SAKI_MATH_SIGNBIT_2019_01_03
#include <saki/math/copysign.h>
#include <saki/math/isnan.h>

namespace saki
{
	/**
	* @brief •‰”‚©‚Ç‚¤‚©”»’è‚·‚é
	* @param x ”»’è‚·‚é’l
	* @return •‰”‚©‚Ç‚¤‚©
	*/
	template<typename T>
	bool signbit(T x)
	{
		return x < static_cast<T>(0);
	}
}
#endif //SAKI_MATH_SIGNBIT_2019_01_03