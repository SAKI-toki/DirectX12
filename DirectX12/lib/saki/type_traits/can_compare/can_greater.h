/**
* @file can_greater.h
* @brief 指定した型が(>)演算子を使用できるかどうか判定するメタ関数
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_CAN_COMPARE_CAN_GREATER_2019_01_22
#define SAKI_TYPE_TRAITS_CAN_COMPARE_CAN_GREATER_2019_01_22
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief より大きい比較できるかどうかを判定する構造体(>)
	*/
	template<typename T>
	struct can_greater
	{
	private:
		template<typename U>
		static constexpr std::true_type greater_check(
			saki::remove_reference_const_t<decltype(std::declval<U>() > std::declval<U>())>*);
		template<typename U>
		static constexpr std::false_type greater_check(...);
	public:
		static constexpr auto value = decltype(greater_check<T>(nullptr))::value;
	};
	/**
	* @brief can_greaterを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto can_greater_v = saki::can_greater<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_COMPARE_CAN_GREATER_2019_01_22