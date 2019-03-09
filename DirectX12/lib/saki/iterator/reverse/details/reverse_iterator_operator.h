/**
* @file reverse_iterator_operator.h
* @brief reverse_iteratorクラスの演算子
* @author 石山 悠
* @date 2019/01/09
*/
#pragma once
#ifndef SAKI_REVERSE_ITERATOR_OPERATOR_2019_01_09
#define SAKI_REVERSE_ITERATOR_OPERATOR_2019_01_09

namespace saki::details
{
	//プロトタイプ宣言
	template<typename T>
	class reverse_iterator_base;
	/**
	* @brief ==演算子
	*/
	template<typename T>
	constexpr bool operator==(const reverse_iterator_base<T>& itr1, const reverse_iterator_base<T>& itr2)
	{
		return itr1.itr == itr2.itr;
	}
	/**
	* @brief !=演算子
	*/
	template<typename T>
	constexpr bool operator!=(const reverse_iterator_base<T>& itr1, const reverse_iterator_base<T>& itr2)
	{
		return !(itr1 == itr2);
	}
}
#endif //SAKI_REVERSE_ITERATOR_OPERATOR_2019_01_09