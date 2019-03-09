/**
* @file array.h
* @brief コンパイル時固定長配列クラス
* @author 石山 悠
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_ARRAY_ARRAY_2019_01_15
#define SAKI_ARRAY_ARRAY_2019_01_15
#include <cstddef>
#include <saki/macro/type_macro.h>
#include <saki/array/details/array_operator.h>

#include <saki/iterator/iterator.h>
#include <saki/iterator/reverse/reverse_iterator.h>

namespace saki
{
	/**
	* @brief コンパイル時固定長配列クラス
	*/
	template<typename T, size_t Size>
	class array
	{
	public:
		SAKI_TYPE_MACRO(T)
	private:
		value_type arr[Size]{};
	public:
		/**
		* @brief 引数なしコンストラクタ
		* @details 全て0で初期化
		*/
		constexpr array()
		{}
		/**
		* @brief 配列の要素だけ値を受け取るコンストラクタ
		* @param u 配列の初期化値
		*/
		template<typename ...U>
		explicit constexpr array(const U& ...u) :
			arr{ u... }
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		array(const array<T, Size>&) = default;
		array<T, Size>& operator=(const array<T, Size>&) = default;
		array(array<T, Size>&&)noexcept = default;
		array<T, Size>& operator=(array<T, Size>&&)noexcept = default;
		/**
		* @brief []演算子
		*/
		constexpr reference operator[](size_t index)
		{
			return arr[index];
		}
		/**
		* @brief []演算子(constexpr)
		*/
		constexpr const_reference operator[](size_t index)const
		{
			return arr[index];
		}
		/**
		* @brief 配列の大きさを取得
		* @return 配列の大きさ
		*/
		constexpr size_type size()const
		{
			return Size;
		}

		//イテレーター
		constexpr saki::iterator<T> begin()
		{
			return saki::iterator<T>(arr);
		}
		constexpr saki::iterator<T> end()
		{
			return saki::iterator<T>(arr + Size);
		}
		constexpr saki::const_iterator<T> begin()const
		{
			return saki::const_iterator<T>(arr);
		}
		constexpr saki::const_iterator<T> end()const
		{
			return saki::const_iterator<T>(arr + Size);
		}

		constexpr saki::const_iterator<T> cbegin()const
		{
			return this->begin();
		}
		constexpr saki::const_iterator<T> cend()const
		{
			return this->end();
		}
		//リバースイテレーター
		constexpr saki::reverse_iterator<saki::iterator<T>> rbegin()
		{
			return saki::reverse_iterator<saki::iterator<T>>(saki::iterator<T>(arr + Size - 1));
		}
		constexpr saki::reverse_iterator<saki::iterator<T>> rend()
		{
			return saki::reverse_iterator<saki::iterator<T>>(saki::iterator<T>(arr - 1));
		}
		constexpr saki::reverse_iterator<saki::const_iterator<T>> rbegin()const
		{
			return saki::reverse_iterator<saki::const_iterator<T>>(saki::const_iterator<T>(arr + Size - 1));
		}
		constexpr saki::reverse_iterator<saki::const_iterator<T>> rend()const
		{
			return saki::reverse_iterator<saki::const_iterator<T>>(saki::const_iterator<T>(arr - 1));
		}

		constexpr saki::reverse_iterator<saki::const_iterator<T>> crbegin()const
		{
			return this->rbegin();
		}
		constexpr saki::reverse_iterator<saki::const_iterator<T>> crend()const
		{
			return this->rend();
		}
	};

	template<typename T>
	class array<T, 0>
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		/**
		* @brief 引数なしコンストラクタ
		*/
		constexpr array()
		{}
	};
}
#endif //SAKI_ARRAY_ARRAY_2019_01_15