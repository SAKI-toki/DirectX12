/**
* @file floor.h
* @brief コンパイル時floor
* @author 石山 悠
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_MATH_FLOOR_2019_01_15
#define SAKI_MATH_FLOOR_2019_01_15
#include <cstddef>
#include <type_traits>
#include <limits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/math/abs.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/fmod.h>
#include <saki/math/log.h>
#include <saki/math/copysign.h>
#include <saki/math/details/pow_n.h>

namespace saki
{
	/**
	* @brief コンパイル時floor
	* @details |x|>uint64_t_maxの場合は何も処理せず返す
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_floating_point_v<T>> = nullptr>
		constexpr T floor(T x)
	{
		if (saki::isnan(x) || saki::isinf(x) || x == 0)return x;
		if (saki::abs(x) > static_cast<T>(std::numeric_limits<int64_t>::max()))
		{
			return x;
		}
		T ans = x - saki::fmod(x, 1);
		if (x < 0 && ans != x)ans -= 1;
		return ans;
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename saki::enable_if_nullptr_t<std::is_integral_v<T>> = nullptr>
		constexpr double floor(T x)
	{
		return saki::floor(static_cast<double>(x));
	}
}
#endif //SAKI_MATH_FLOOR_2019_01_15