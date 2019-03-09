/**
* @file can_end_method.h
* @brief 指定した型がstd::endできるかどうか判定するメタ関数
* @author 石山 悠
* @date 2019/01/12
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_CAN_END_METHOD_2019_01_12
#define SAKI_TYPE_TRAITS_CAN_END_METHOD_2019_01_12
#include <type_traits>
#include <utility>
#include <iterator>
namespace saki
{
	/**
	* @brief endできるかどうかを判定する構造体
	*/
	template<typename T>
	struct can_end
	{
	private:
		template<typename U>
		static constexpr std::true_type end_check(decltype(std::begin(std::declval<U>()))* u);
		template<typename U>
		static constexpr std::false_type end_check(...);
	public:
		static constexpr auto value = decltype(end_check<T>(nullptr))::value;
	};
	/**
	* @brief can_endを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto can_end_v = saki::can_end<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_END_METHOD_2019_01_12