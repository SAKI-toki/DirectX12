/**
* @file logb.h
* @brief �R���p�C����logb
* @author �ΎR �I
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_MATH_LOGB_2019_01_15
#define SAKI_MATH_LOGB_2019_01_15
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/log2.h>
#include <saki/math/abs.h>
#include <saki/math/floor.h>

namespace saki
{
	/**
	* @brief �R���p�C����logb
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T logb(T x)
	{
		return saki::floor(saki::log2(saki::abs(x)));
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double logb(T x)
	{
		return saki::logb(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_LOGB_2019_01_15