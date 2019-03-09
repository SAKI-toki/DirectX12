/**
* @file reverse_iterator_operator.h
* @brief reverse_iterator�N���X�̉��Z�q
* @author �ΎR �I
* @date 2019/01/09
*/
#pragma once
#ifndef SAKI_REVERSE_ITERATOR_OPERATOR_2019_01_09
#define SAKI_REVERSE_ITERATOR_OPERATOR_2019_01_09

namespace saki::details
{
	//�v���g�^�C�v�錾
	template<typename T>
	class reverse_iterator_base;
	/**
	* @brief ==���Z�q
	*/
	template<typename T>
	constexpr bool operator==(const reverse_iterator_base<T>& itr1, const reverse_iterator_base<T>& itr2)
	{
		return itr1.itr == itr2.itr;
	}
	/**
	* @brief !=���Z�q
	*/
	template<typename T>
	constexpr bool operator!=(const reverse_iterator_base<T>& itr1, const reverse_iterator_base<T>& itr2)
	{
		return !(itr1 == itr2);
	}
}
#endif //SAKI_REVERSE_ITERATOR_OPERATOR_2019_01_09