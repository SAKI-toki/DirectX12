/**
* @file isnan.h
* @brief Not a Numberかどうか判定する関数
* @author 石山 悠
* @date 2019/01/02
*/
#pragma once
#ifndef SAKI_MATH_ISNAN_2019_01_02
#define SAKI_MATH_ISNAN_2019_01_02
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief Not a Numberかどうか判定
	* @param x 判定する値
	* @return NaNかどうか
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
	constexpr bool isnan(T x)
	{
		return !(x == x);
	}
	/**
	* @brief Not a Numberかどうか判定
	* @param x 判定する値
	* @details floating_point以外はfalse
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<!std::is_floating_point_v<T>> = nullptr>
		constexpr bool isnan(T)
	{
		return false;
	}
}
#endif //SAKI_MATH_ISNAN_2019_01_02