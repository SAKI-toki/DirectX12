/**
* @file digit_count.h
* @brief 整数部の桁数を数える
* @author 石山 悠
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_MATH_DIGIT_COUNT_2019_01_15
#define SAKI_MATH_DIGIT_COUNT_2019_01_15
#include <cstddef>
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/abs.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief 整数部の桁数を数える関数
	* @details log10でも可能だが、整数部だけならこちらを使ったほうが良い
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_arithmetic_v<T>> = nullptr>
		constexpr size_t digit_count(T x)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			if (saki::isnan(x) || saki::isinf(x))return 0;
		}
		if (std::is_signed_v<T>)
		{
			x = saki::abs(x);
		}
		if (x < 1)return 1;
		size_t count = 0;
		while (x >= 1)
		{
			++count;
			x /= 10;
		}
		return count;
	}
}
#endif //SAKI_MATH_DIGIT_COUNT_2019_01_15