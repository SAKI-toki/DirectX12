/**
* @file enable_if_nullptr.h
* @brief nullptr_t‚ğ•Ô‚·enabled_if
* @author ÎR —I
* @date 2019/01/19
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_ENABLE_IF_NULLPTR_2019_01_19
#define SAKI_TYPE_TRAITS_ENABLE_IF_NULLPTR_2019_01_19
#include <cstddef>

namespace saki
{
	/**
	* @brief enalbe_if‚Ìfalse
	*/
	template<bool>
	struct enable_if_nullptr
	{
	};
	/**
	* @brief enable_if‚Ìtrue
	*/
	template<>
	struct enable_if_nullptr<true>
	{
		using type = std::nullptr_t;
	};
	/**
	* @brief enable_if_nullptr‚ğŠÈ’P‚ÉŒÄ‚Ño‚¹‚é•Ï”
	*/
	template<bool Con>
	using enable_if_nullptr_t = typename enable_if_nullptr<Con>::type;
}
#endif //SAKI_TYPE_TRAITS_ENABLE_IF_NULLPTR_2019_01_19