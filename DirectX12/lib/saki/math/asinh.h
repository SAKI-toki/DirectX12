/**
* @file asinh.h
* @brief �R���p�C����asinh
* @author �ΎR �I
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_MATH_ASINH_2019_01_08
#define SAKI_MATH_ASINH_2019_01_08
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/log.h>
#include <saki/math/sqrt.h>

namespace saki
{
	/**
	* @brief �R���p�C����asinh
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T asinh(T x)
	{
		if (saki::isnan(x) || saki::isinf(x) || x == 0)return x;

		return saki::log(x + saki::sqrt(x * x + 1));
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double asinh(T x)
	{
		return saki::asinh(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_ASINH_2019_01_08