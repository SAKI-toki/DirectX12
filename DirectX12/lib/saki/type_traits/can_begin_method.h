/**
* @file can_begin_method.h
* @brief 指定した型がstd::beginできるかどうか判定するメタ関数
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_BEGIN_METHOD_2018_12_13
#define SAKI_TYPE_TRAITS_BEGIN_METHOD_2018_12_13
#include <type_traits>
#include <utility>
#include <iterator>
namespace saki
{
	/**
	* @brief beginできるかどうかを判定する構造体
	*/
	template<typename T>
	struct can_begin
	{
	private:
		template<typename U>
		static constexpr std::true_type begin_check(decltype(std::begin(std::declval<U>()))* u);
		template<typename U>
		static constexpr std::false_type begin_check(...);
	public:
		static constexpr auto value = decltype(begin_check<T>(nullptr))::value;
	};
	/**
	* @brief can_beginを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto can_begin_v = saki::can_begin<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_BEGIN_METHOD_2018_12_13