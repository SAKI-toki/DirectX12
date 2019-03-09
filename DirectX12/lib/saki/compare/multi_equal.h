/**
* @file multi_equal.h
* @brief 複数の比較を一度に行う(==)
* @author 石山 悠
* @date 2019/01/18
*/
#pragma once
#ifndef SAKI_COMPARE_MULTI_EQUAL_2019_01_18
#define SAKI_COMPARE_MULTI_EQUAL_2019_01_18
#include <type_traits>
#include <saki/type_traits/can_compare/can_equal_equal.h>

namespace saki
{
	namespace impl
	{
		/**
		* @brief 比較するものがない(なくなった)場合、falseを返す
		*/
		template<typename T>
		constexpr bool multi_equal_impl(const T&)
		{
			return false;
		}
		/**
		* @brief multi_equalの実装部
		* @details 毎回isnanを判定する必要がないため、実装部を分けた
		*/
		template<typename First, typename Second, typename ...Args>
		constexpr bool multi_equal_impl(const First& first, Second second, const Args& ...args)
		{
			return (first == static_cast<First>(second)) ? true : saki::impl::multi_equal_impl(first, (args)...);
		}
	}
	/**
	* @brief 複数の比較を一度に行える
	* @details if(x == 1 || x == 2 || x == 3)をmulti_equal(x,1,2,3)と書ける
	*/
	template<typename First, typename ...Args,
	typename saki::enable_if_nullptr_t<
		std::conjunction_v<std::is_convertible<First, Args>...>&&	//最初以外の型がFirstに変換可能か
		std::conjunction_v<saki::can_equal_equal<First>>			//Firstが==演算子が有効かどうか
	> = nullptr>
	constexpr bool multi_equal(const First& first, const Args& ...args)
	{
		return saki::impl::multi_equal_impl(first, (args)...);
	}
}
#endif //SAKI_COMPARE_MULTI_EQUAL_2019_01_18