/**
* @file remove_reference_const.h
* @brief 参照とconst修飾を削除した型を返す
* @author 石山 悠
* @date 2019/01/12
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_REMOVE_REFERENCE_CONST_2019_01_12
#define SAKI_TYPE_TRAITS_REMOVE_REFERENCE_CONST_2019_01_12
#include <type_traits>

namespace saki
{
	/**
	* @brief 参照とconst修飾を削除
	*/
	template<typename T>
	struct remove_reference_const
	{
		using type = typename std::remove_const_t<std::remove_reference_t<T>>;
	};
	/**
	* @brief remove_reference_constを簡単に呼び出せるようにした 
	*/
	template<typename T>
	using remove_reference_const_t = typename saki::remove_reference_const<T>::type;
}
#endif //SAKI_TYPE_TRAITS_REMOVE_REFERENCE_CONST_2019_01_12