/**
* @file degree_radian_conversion.h
* @brief Degree����Radian�ARadian����Degree�ւ̕ϊ�
* @author �ΎR �I
* @date 2019/01/19
*/
#pragma once
#ifndef SAKI_MATH_DEGREE_RADIAN_CONVERSION_2019_01_19
#define SAKI_MATH_DEGREE_RADIAN_CONVERSION_2019_01_19
#include <type_traits>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/pi.h>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief Degree����Radian�ɕϊ�
	* @param deg Radian�ɕϊ�����Degree
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
	constexpr T to_radian(T deg)
	{
		if (saki::isnan(deg) || saki::isinf(deg) || deg == 0)return deg;
		return static_cast<T>(deg * 0.0174532925199389);
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double to_radian(T deg)
	{
		return saki::to_radian(static_cast<double>(deg));
	}
	/**
	* @brief Radian����Degree�ɕϊ�
	* @param rad Degree�ɕϊ�����Radian
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
	constexpr T to_degree(T rad)
	{
		if (saki::isnan(rad) || saki::isinf(rad) || rad == 0)return rad;
		return static_cast<T>(rad * 57.29577951309679);
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double to_degree(T rad)
	{
		return saki::to_degree(static_cast<double>(rad));
	}
}
#endif //SAKI_MATH_DEGREE_RADIAN_CONVERSION_2019_01_19