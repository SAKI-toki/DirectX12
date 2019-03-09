/**
* @file split.h
* @brief •¶š—ñ‚Ì•ªŠ„
* @author ÎR —I
* @date 2018/12/23
*/
#pragma once
#ifndef SAKI_SPLIT_SPLIT_2018_12_23
#define SAKI_SPLIT_SPLIT_2018_12_23
#include <string>
#include <vector>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/split/details/multiple_separation.h>
#include <saki/split/details/not_equal_separation.h>
#include <saki/type_traits/has_check_method.h>

namespace saki
{
	/**
	* @brief stringŒ^‚ğw’è‚³‚ê‚½•¶š‚Å‹æØ‚Á‚½‚à‚Ì‚ğvector‚Å•Ô‚·
	* @param str ‹æØ‚é‘ÎÛ‚Ì•¶š—ñ
	* @param split_separation ‹æØ‚è‚ğ•¡”‘I‘ğ‚Å‚«‚éƒNƒ‰ƒX
	* @return ‹æØ‚Á‚½•¶š—ñ‚ğŠi”[‚·‚évectorƒNƒ‰ƒX
	* @details bool check(char)‚ÌŠÖ”‚ğ‚Á‚Ä‚¢‚éƒNƒ‰ƒX‚È‚ç‚È‚ñ‚Å‚àó‚¯æ‚êAfalse‚ÌŠÔ•¶š‚ğŠi”[‚µ‘±‚¯‚Ü‚·
	*/
	template<template<typename, typename> typename Container = std::vector, typename T,
		typename saki::enable_if_nullptr_t<saki::has_check_v<T>> = nullptr>
		Container<std::string, std::allocator<std::string>> split(const std::string& str, T&& split_separation)
	{
		//‹æØ‚Á‚½•¶š—ñ‚ğ’Ç‰Á
		std::vector<std::string> str_list;
		size_t index = 0;
		auto begin = std::begin(str);
		while (index < str.size())
		{
			size_t start_index = index;
			while (index < str.size() && !split_separation.check(str[index]))
			{
				++index;
			}
			str_list.push_back(std::string(begin + start_index, begin + index));
			++index;
		}
		//Œ^‚ªstd::vector‚È‚ç‚»‚Ì‚Ü‚Üstr_list‚ğ•Ô‚·
		if constexpr (std::is_same_v<Container<std::string, std::allocator<std::string>>,
			std::vector<std::string, std::allocator<std::string>>>)
		{
			return str_list;
		}
		//Œ^‚ªstd::list‚Ì‚æ‚¤‚É•Ê‚ÌŒ^‚È‚ç‚»‚ê‚É•ÏŠ·‚µ‚Ä‚©‚ç•Ô‚·
		else
		{
			Container<std::string, std::allocator<std::string>> return_str_list(std::begin(str_list), std::end(str_list));
			return return_str_list;
		}
	}

	/**
	* @brief stringŒ^‚ğw’è‚³‚ê‚½•¶š‚Å‹æØ‚Á‚½‚à‚Ì‚ğvector‚Å•Ô‚·
	* @param str ‹æØ‚é‘ÎÛ‚Ì•¶š—ñ
	* @param first_separation 1‚Â–Ú‚Ì‹æØ‚è•¶š
	* @param t 2‚Â–ÚˆÈ~‚Ì‹æØ‚è•¶š
	* @return ‹æØ‚Á‚½•¶š—ñ‚ğŠi”[‚·‚évectorƒNƒ‰ƒX
	*/
	template<template<typename, typename> typename Container = std::vector,
		typename First, typename ...T>
		Container<std::string, std::allocator<std::string>> split(const std::string& str, First first_separation, T ...t)
	{
		return saki::split<Container>(str, saki::MultipleSeparation(first_separation, t...));
	}
}
#endif //SAKI_SPLIT_SPLIT_2018_12_23