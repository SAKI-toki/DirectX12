/**
* @file exchange.h
* @brief �R���p�C����exchange
* @author �ΎR �I
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_MATH_EXCHANGE_2018_11_21
#define SAKI_MATH_EXCHANGE_2018_11_21
#include <type_traits>
#include <utility>

namespace saki
{
	/**
	* @brief �R���p�C����exchange
	* @param obj �l��������l
	* @param new_val �l�ɓ����l
	*/
	template<typename T, typename U = T>
	constexpr T exchange(T& obj, U&& new_val)
	{
		T t1 = std::move(obj);
		obj = std::forward<U>(new_val);
		return t1;
	}
}
#endif //SAKI_MATH_EXCHANGE_2018_11_21