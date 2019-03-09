/**
* @file ilogb.h
* @brief �R���p�C����ilogb
* @author �ΎR �I
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
	* @brief �R���p�C����ilogb
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
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr int ilogb(T x)
	{
		return saki::ilogb(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_ILOGB_2019_01_15