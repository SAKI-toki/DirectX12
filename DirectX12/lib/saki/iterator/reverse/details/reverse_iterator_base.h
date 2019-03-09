/**
* @file reverse_iterator_base.h
* @brief ���o�[�X�C�e���[�^�[�̃x�[�X�N���X
* @author �ΎR �I
* @date 2019/01/14
*/
#pragma once
#ifndef SAKI_ITERATOR_REVERSE_DETAILS_REVERSE_ITERATOR_BASE_2019_01_14
#define SAKI_ITERATOR_REVERSE_DETAILS_REVERSE_ITERATOR_BASE_2019_01_14
#include <saki/iterator/reverse/details/reverse_iterator_operator.h>

namespace saki::details
{
	/**
	* @brief �A���[���Z�q���ĂԊ֐�
	*/
	template<typename Iterator>
	constexpr decltype(auto) operator_arrow(Iterator&& itr)
	{
		return std::forward<Iterator>(itr).operator->();
	}
	/**
	* @brief ���o�[�X�C�e���[�^�[�̃x�[�X�N���X
	*/
	template<typename T>
	class reverse_iterator_base
	{
		//�񃁃��o��r���Z�q��friend�w��
		template<typename TT>
		friend constexpr bool operator==(const reverse_iterator_base<TT>& itr1, const reverse_iterator_base<TT>& itr2);
		template<typename TT>
		friend constexpr bool operator!=(const reverse_iterator_base<TT>& itr1, const reverse_iterator_base<TT>& itr2);
	public:
		//SAKI_TYPE_MACRO(T)
	protected:
		T itr;
	public:
		explicit constexpr reverse_iterator_base(T _itr) :itr(_itr) {}
		/**
		* @brief �ԐڎQ�Ɖ��Z�q
		*/
		constexpr typename T::reference operator*()const
		{
			return *itr;
		}
		/**
		* @brief �A���[���Z�q
		*/
		constexpr typename T::pointer operator->()const
		{
			return saki::details::operator_arrow(itr);
		}
		/**
		* @brief ++���Z�q(�O�u)
		*/
		constexpr saki::details::reverse_iterator_base<T>& operator++()
		{
			--(this->itr);
			return *this;
		}
		/**
		* @brief ++���Z�q(��u)
		*/
		constexpr saki::details::reverse_iterator_base<T> operator++(int)
		{
			saki::details::reverse_iterator_base<T> temp = itr;
			--(this->itr);
			return temp;
		}
		/**
		* @brief --���Z�q(�O�u)
		*/
		constexpr saki::details::reverse_iterator_base<T>& operator--()
		{
			++(this->itr);
			return *this;
		}
		/**
		* @brief --���Z�q(��u)
		*/
		constexpr saki::details::reverse_iterator_base<T> operator--(int)
		{
			saki::details::reverse_iterator_base<T> temp = itr;
			++(this->itr);
			return temp;
		}
	};
}
#endif //SAKI_ITERATOR_REVERSE_DETAILS_REVERSE_ITERATOR_BASE_2019_01_14