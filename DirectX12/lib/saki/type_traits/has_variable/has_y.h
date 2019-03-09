/**
* @file has_y.h
* @brief 指定した型が変数yを持っているかどうか判定するメタ関数
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Y_2019_01_22
#define SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Y_2019_01_22
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief 変数yを持っているかどうかを判定する構造体
	*/
	template<typename T>
	struct has_y
	{
	private:
		template<typename U>
		static constexpr std::true_type y_check(saki::remove_reference_const_t<decltype(std::declval<U>().y)>*);
		template<typename U>
		static constexpr std::false_type y_check(...);
	public:
		static constexpr auto value = decltype(y_check<T>(nullptr))::value;
	};
	/**
	* @brief has_yを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto has_y_v = saki::has_y<T>::value;
}
#endif //SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Y_2019_01_22