/**
* @file iterator_base.h
* @brief イテレーターのベースクラス
* @author 石山 悠
* @date 2019/01/13
*/
#pragma once
#ifndef SAKI_ITERATOR_DETAILS_ITERATOR_BASE_2019_01_13
#define SAKI_ITERATOR_DETAILS_ITERATOR_BASE_2019_01_13
#include <saki/iterator/details/iterator_operator.h>

namespace saki::details
{
	/**
	* @brief イテレーターのベースクラス 
	*/
	template<typename T>
	class iterator_base
	{
		//非メンバ比較演算子をfriend指定
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
		* @brief ポインタで初期化するコンストラクタ
		*/
		explicit constexpr iterator_base(T* pointer) : itr(pointer) {}
		/**
		* @brief 間接参照演算子
		*/
		constexpr T& operator*()const
		{
			return *itr;
		}
		/**
		* @brief アロー演算子
		*/
		constexpr T* operator->()const
		{
			return itr;
		}
		/**
		* @brief ++演算子(前置)
		*/
		constexpr saki::details::iterator_base<T>& operator++()
		{
			this->itr += 1;
			return *this;
		}
		/**
		* @brief ++演算子(後置)
		*/
		constexpr saki::details::iterator_base<T> operator++(int)
		{
			saki::details::iterator_base<T> temp = *this;
			this->itr += 1;
			return temp;
		}
		/**
		* @brief --演算子(前置)
		*/
		constexpr saki::details::iterator_base<T>& operator--()
		{
			this->itr -= 1;
			return *this;
		}
		/**
		* @brief --演算子(後置)
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