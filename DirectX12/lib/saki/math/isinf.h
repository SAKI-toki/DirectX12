/**
* @file isinf.h
* @brief コンパイル時isinf
* @author 石山 悠
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_MATH_ISINF_2019_01_08
#define SAKI_MATH_ISINF_2019_01_08
#include <limits>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief コンパイル時isinf
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
	constexpr bool isinf(T x)
	{
		return x == std::numeric_limits<T>::infinity() ||
			x == -std::numeric_limits<T>::infinity();
	}
	/**
	* @brief コンパイル時isinf
	* @details floating_point以外はfalse
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<!std::is_floating_point_v<T>> = nullptr>
		constexpr bool isinf(T)
	{
		return false;
	}
}
#endif //SAKI_MATH_ISINF_2019_01_08