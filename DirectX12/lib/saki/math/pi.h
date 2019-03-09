/**
* @file pi.h
* @brief 円周率のテンプレート変数
* @author 石山 悠
* @date 2018/10/15
*/
#pragma once
#ifndef SAKI_MATH_PI_2018_10_15
#define SAKI_MATH_PI_2018_10_15
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief 円周率のテンプレート変数
	*/
	template<typename T = double,
		typename saki::enable_if_nullptr_t<std::is_arithmetic_v<T>> = nullptr>
	static constexpr auto PI =
		static_cast<T>(3.14159265358979323846);
	/**
	* @brief 円周率の1/2のテンプレート変数
	*/
	template<typename T = double,
		typename saki::enable_if_nullptr_t<std::is_arithmetic_v<T>> = nullptr>
	static constexpr auto PI_HALF = static_cast<T>(PI<double> / 2);
	/**
	* @brief 円周率の1/4のテンプレート変数
	*/
	template<typename T = double,
		typename saki::enable_if_nullptr_t<std::is_arithmetic_v<T>> = nullptr>
	static constexpr auto PI_QUARTER = static_cast<T>(PI<double> / 4);
}
#endif //SAKI_MATH_PI_2018_10_15