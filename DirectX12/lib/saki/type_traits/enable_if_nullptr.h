/**
* @file enable_if_nullptr.h
* @brief nullptr_t��Ԃ�enabled_if
* @author �ΎR �I
* @date 2019/01/19
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_ENABLE_IF_NULLPTR_2019_01_19
#define SAKI_TYPE_TRAITS_ENABLE_IF_NULLPTR_2019_01_19
#include <cstddef>

namespace saki
{
	/**
	* @brief enalbe_if��false
	*/
	template<bool>
	struct enable_if_nullptr
	{
	};
	/**
	* @brief enable_if��true
	*/
	template<>
	struct enable_if_nullptr<true>
	{
		using type = std::nullptr_t;
	};
	/**
	* @brief enable_if_nullptr���ȒP�ɌĂяo����ϐ�
	*/
	template<bool Con>
	using enable_if_nullptr_t = typename enable_if_nullptr<Con>::type;
}
#endif //SAKI_TYPE_TRAITS_ENABLE_IF_NULLPTR_2019_01_19