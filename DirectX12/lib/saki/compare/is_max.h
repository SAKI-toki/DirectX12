/**
* @file is_max.h
* @brief 複数の比較を一度に行う(>=)
* @author 石山 悠
* @date 2019/01/21
*/
#pragma once
#ifndef SAKI_COMPARE_IS_MAX_2019_01_21
#define SAKI_COMPARE_IS_MAX_2019_01_21
#include <type_traits>
#include <saki/type_traits/can_compare/can_less.h>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	namespace impl
	{
		/**
		* @brief 比較するものがない(なくなった)場合、trueを返す
		*/
		template<typename T>
		constexpr bool is_max_impl(const T&)
		{
			return true;
		}
		/**
		* @brief is_maxの実装部
		* @details 毎回isnanを判定する必要がないため、実装部を分けた
		*/
		template<typename First, typename Second, typename ...Args>
		constexpr bool is_max_impl(const First& first, Second second, const Args& ...args)
		{
			return (first < static_cast<First>(second)) ? false : saki::impl::is_max_impl(first, (args)...);
		}
	}
	/**
	* @brief 複数の比較を一度に行える(>=)
	* @details if(x >= a && x >= b && x >= c)をis_max(x,a,b,c)と書ける
	*/
	template<typename First, typename ...Args,
		typename saki::enable_if_nullptr_t <
		std::conjunction_v<std::is_convertible<Args, First>...>&&	//最初以外の型がFirstに変換可能か
		std::conjunction_v<saki::can_less<First>>					//Firstが<演算子が有効かどうか
	> = nullptr>
		constexpr bool is_max(const First& first, const Args& ...args)
	{
		return saki::impl::is_max_impl(first, (args)...);
	}
}
#endif //SAKI_COMPARE_IS_MAX_2019_01_21