/**
* @file has_z.h
* @brief 指定した型が変数zを持っているかどうか判定するメタ関数
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Z_2019_01_22
#define SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Z_2019_01_22
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief 変数yを持っているかどうかを判定する構造体
	*/
	template<typename T>
	struct has_z
	{
	private:
		template<typename U>
		static constexpr std::true_type z_check(saki::remove_reference_const_t<decltype(std::declval<U>().z)>*);
		template<typename U>
		static constexpr std::false_type z_check(...);
	public:
		static constexpr auto value = decltype(z_check<T>(nullptr))::value;
	};
	/**
	* @brief has_zを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto has_z_v = saki::has_z<T>::value;
}
#endif //SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Z_2019_01_22