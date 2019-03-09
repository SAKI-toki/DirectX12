/**
* @file reverse_iterator_base.h
* @brief リバースイテレーターのベースクラス
* @author 石山 悠
* @date 2019/01/14
*/
#pragma once
#ifndef SAKI_ITERATOR_REVERSE_DETAILS_REVERSE_ITERATOR_BASE_2019_01_14
#define SAKI_ITERATOR_REVERSE_DETAILS_REVERSE_ITERATOR_BASE_2019_01_14
#include <saki/iterator/reverse/details/reverse_iterator_operator.h>

namespace saki::details
{
	/**
	* @brief アロー演算子を呼ぶ関数
	*/
	template<typename Iterator>
	constexpr decltype(auto) operator_arrow(Iterator&& itr)
	{
		return std::forward<Iterator>(itr).operator->();
	}
	/**
	* @brief リバースイテレーターのベースクラス
	*/
	template<typename T>
	class reverse_iterator_base
	{
		//非メンバ比較演算子をfriend指定
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
		* @brief 間接参照演算子
		*/
		constexpr typename T::reference operator*()const
		{
			return *itr;
		}
		/**
		* @brief アロー演算子
		*/
		constexpr typename T::pointer operator->()const
		{
			return saki::details::operator_arrow(itr);
		}
		/**
		* @brief ++演算子(前置)
		*/
		constexpr saki::details::reverse_iterator_base<T>& operator++()
		{
			--(this->itr);
			return *this;
		}
		/**
		* @brief ++演算子(後置)
		*/
		constexpr saki::details::reverse_iterator_base<T> operator++(int)
		{
			saki::details::reverse_iterator_base<T> temp = itr;
			--(this->itr);
			return temp;
		}
		/**
		* @brief --演算子(前置)
		*/
		constexpr saki::details::reverse_iterator_base<T>& operator--()
		{
			++(this->itr);
			return *this;
		}
		/**
		* @brief --演算子(後置)
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