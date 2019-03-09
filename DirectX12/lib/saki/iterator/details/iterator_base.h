/**
* @file iterator_base.h
* @brief �C�e���[�^�[�̃x�[�X�N���X
* @author �ΎR �I
* @date 2019/01/13
*/
#pragma once
#ifndef SAKI_ITERATOR_DETAILS_ITERATOR_BASE_2019_01_13
#define SAKI_ITERATOR_DETAILS_ITERATOR_BASE_2019_01_13
#include <saki/iterator/details/iterator_operator.h>

namespace saki::details
{
	/**
	* @brief �C�e���[�^�[�̃x�[�X�N���X 
	*/
	template<typename T>
	class iterator_base
	{
		//�񃁃��o��r���Z�q��friend�w��
		template<typename TT>
		friend constexpr bool operator==(const iterator_base<TT>& itr1, const iterator_base<TT>& itr2);
		template<typename TT>
		friend constexpr bool operator!=(const iterator_base<TT>& itr1, const iterator_base<TT>& itr2);
	public:
		SAKI_TYPE_MACRO(T)
	protected:
		T* itr;
	public:
		/**
		* @brief �|�C���^�ŏ���������R���X�g���N�^
		*/
		explicit constexpr iterator_base(T* pointer) : itr(pointer) {}
		/**
		* @brief �ԐڎQ�Ɖ��Z�q
		*/
		constexpr T& operator*()const
		{
			return *itr;
		}
		/**
		* @brief �A���[���Z�q
		*/
		constexpr T* operator->()const
		{
			return itr;
		}
		/**
		* @brief ++���Z�q(�O�u)
		*/
		constexpr saki::details::iterator_base<T>& operator++()
		{
			this->itr += 1;
			return *this;
		}
		/**
		* @brief ++���Z�q(��u)
		*/
		constexpr saki::details::iterator_base<T> operator++(int)
		{
			saki::details::iterator_base<T> temp = *this;
			this->itr += 1;
			return temp;
		}
		/**
		* @brief --���Z�q(�O�u)
		*/
		constexpr saki::details::iterator_base<T>& operator--()
		{
			this->itr -= 1;
			return *this;
		}
		/**
		* @brief --���Z�q(��u)
		*/
		constexpr saki::details::iterator_base<T> operator--(int)
		{
			saki::details::iterator_base<T> temp = *this;
			this->itr -= 1;
			return temp;
		}
	};
}
#endif //SAKI_ITERATOR_DETAILS_ITERATOR_BASE_2019_01_13