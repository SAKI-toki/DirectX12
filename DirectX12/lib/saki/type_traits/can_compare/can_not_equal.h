/**
* @file can_not_equal.h
* @brief 指定した型が(!=)演算子を使用できるかどうか判定するメタ関数
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_CAN_COMPARE_CAN_NOT_EQUAL_2019_01_22
#define SAKI_TYPE_TRAITS_CAN_COMPARE_CAN_NOT_EQUAL_2019_01_22
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief ノットイコール比較できるかどうかを判定する構造体(!=)
	*/
	template<typename T>
	struct can_not_equal
	{
	private:
		template<typename U>
		static constexpr std::true_type not_equal_check(
			saki::remove_reference_const_t<decltype(std::declval<U>() != std::declval<U>())>*);
		template<typename U>
		static constexpr std::false_type not_equal_check(...);
	public:
		static constexpr auto value = decltype(not_equal_check<T>(nullptr))::value;
	};
	/**
	* @brief can_not_equalを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto can_not_equal_v = saki::can_not_equal<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_COMPARE_CAN_NOT_EQUAL_2019_01_22