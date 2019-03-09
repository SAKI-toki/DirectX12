/**
* @file split.h
* @brief ������̕���
* @author �ΎR �I
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
	* @brief string�^���w�肳�ꂽ�����ŋ�؂������̂�vector�ŕԂ�
	* @param str ��؂�Ώۂ̕�����
	* @param split_separation ��؂�𕡐��I���ł���N���X
	* @return ��؂�����������i�[����vector�N���X
	* @details bool check(char)�̊֐��������Ă���N���X�Ȃ�Ȃ�ł��󂯎��Afalse�̊ԕ������i�[�������܂�
	*/
	template<template<typename, typename> typename Container = std::vector, typename T,
		typename saki::enable_if_nullptr_t<saki::has_check_v<T>> = nullptr>
		Container<std::string, std::allocator<std::string>> split(const std::string& str, T&& split_separation)
	{
		//��؂����������ǉ�
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
		//�^��std::vector�Ȃ炻�̂܂�str_list��Ԃ�
		if constexpr (std::is_same_v<Container<std::string, std::allocator<std::string>>,
			std::vector<std::string, std::allocator<std::string>>>)
		{
			return str_list;
		}
		//�^��std::list�̂悤�ɕʂ̌^�Ȃ炻��ɕϊ����Ă���Ԃ�
		else
		{
			Container<std::string, std::allocator<std::string>> return_str_list(std::begin(str_list), std::end(str_list));
			return return_str_list;
		}
	}

	/**
	* @brief string�^���w�肳�ꂽ�����ŋ�؂������̂�vector�ŕԂ�
	* @param str ��؂�Ώۂ̕�����
	* @param first_separation 1�ڂ̋�؂蕶��
	* @param t 2�ڈȍ~�̋�؂蕶��
	* @return ��؂�����������i�[����vector�N���X
	*/
	template<template<typename, typename> typename Container = std::vector,
		typename First, typename ...T>
		Container<std::string, std::allocator<std::string>> split(const std::string& str, First first_separation, T ...t)
	{
		return saki::split<Container>(str, saki::MultipleSeparation(first_separation, t...));
	}
}
#endif //SAKI_SPLIT_SPLIT_2018_12_23