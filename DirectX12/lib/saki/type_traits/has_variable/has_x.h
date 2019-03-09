/**
* @file has_x.h
* @brief 指定した型が変数xを持っているかどうか判定するメタ関数
* @author 石山 悠
* @date 2018/12/29
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_X_2018_12_23
#define SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_X_2018_12_23
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief 変数xを持っているかどうかを判定する構造体
	*/
	template<typename T>
	struct has_x
	{
	private:
		template<typename U>
		static constexpr std::true_type x_check(saki::remove_reference_const_t<decltype(std::declval<U>().x)>*);
		template<typename U>
		static constexpr std::false_type x_check(...);
	public:
		static constexpr auto value = decltype(x_check<T>(nullptr))::value;
	};
	/**
	* @brief has_xを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto has_x_v = saki::has_x<T>::value;
}
#endif //SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_X_2018_12_23