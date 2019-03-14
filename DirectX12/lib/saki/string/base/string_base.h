/**
* @file string_base.h
* @brief コンパイル時固定長stringクラスのベースクラス
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_STRING_BASE_STRING_BASE_2019_01_22
#define SAKI_STRING_BASE_STRING_BASE_2019_01_22
#include <cstddef>
#include <ostream>
#include <utility>
#include <saki/macro/type_macro.h>
#include <saki/array/array.h>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief コンパイル時固定長string_baseクラス
	*/
	template<typename T, size_t Size>
	class string_base
	{
	public:
		SAKI_TYPE_MACRO(T)
	private:
		saki::array<T, Size> str{};
	public:
		/**
		* @brief 引数なしコンストラクタ
		*/
		constexpr string_base()
		{
			for (size_t i = 0; i < Size; ++i)
			{
				str[i] = '\0';
			}
		}
		/**
		* @brief 文字列からの初期化
		*/
		constexpr string_base(const_pointer _str)
		{
			size_t i = 0;
			for (; i < Size&&_str[i] != '\0'; ++i)
			{
				str[i] = _str[i];
			}
			if (i != Size)str[i] = '\0';
		}
		constexpr string_base<T, Size>& operator=(const_pointer _str)
		{
			size_t i = 0;
			for (; i < Size&&_str[i] != '\0'; ++i)
			{
				str[i] = _str[i];
			}
			if (i != Size)str[i] = '\0';
			return *this;
		}
		template<size_t N>
		constexpr string_base(const string_base<T, N>& _string)
		{
			size_t copy_size = (N < Size) ? N : Size;
			for (size_t i = 0; i < copy_size; ++i)
			{
				str[i] = _string[i];
			}
		}
		template<size_t N>
		constexpr string_base<T, Size> operator=(const string_base<T, N>& _string)
		{
			size_t copy_size = (N < Size) ? N : Size;
			for (size_t i = 0; i < copy_size; ++i)
			{
				str[i] = _string[i];
			}
			return *this;
		}

		/**
		* @brief 文字列の大きさを取得
		* @return 文字列の大きさ
		*/
		constexpr size_type size()const
		{
			return Size;
		}
		constexpr reference operator[](size_t index)
		{
			return str[index];
		}
		constexpr const_reference operator[](size_t index)const
		{
			return str[index];
		}

		//フレンド関数
		template<typename TT, size_t N>
		friend std::ostream& operator<<(std::ostream&, const string_base<TT, N>&);
	};

	/**
	* @brief stringの出力
	*/
	template<typename T, size_t N>
	std::ostream& operator<<(std::ostream& os, const string_base<T, N>& str)
	{
		size_t i = 0;
		for (; i < N && str[i] != '\0'; ++i)
		{
			os << str[i];
		}
		if (str[i - 1] != '\0')
		{
			os << '\0';
		}
		return os;
	}

	template<typename T,size_t N>
	constexpr bool operator==(const saki::string_base<T, N>& str1, const char* str2)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (str1[i] == '\0'&&str2[i] == '\0')
			{
				return true;
			}
			if (str1[i] != '\0'&&str2[i] == '\0')
			{
				return false;
			}
			if (str1[i] == '\0'&&str2[i] != '\0')
			{
				return false;
			}
			if (str1[i] != str2[i])
			{
				return false;
			}
		}
		return true;
	}
	template<typename T, size_t N>
	constexpr bool operator!=(const saki::string_base<T, N>& str1, const char* str2)
	{
		return !(str1 == str2);
	}
	template<typename T, size_t N>
	constexpr bool operator==(const char* str1, const saki::string_base<T, N>& str2)
	{
		return str2 == str1;
	}
	template<typename T, size_t N>
	constexpr bool operator!=(const char* str1, const saki::string_base<T, N>& str2)
	{
		return str2 != str1;
	}
	template<typename T,size_t N>
	constexpr bool operator==(const saki::string_base<T, N>& str1, const saki::string_base<T, N>& str2)
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (str1[i] != str2[i])
			{
				return false;
			}
		}
		return true;
	}
	template<typename T, size_t N>
	constexpr bool operator!=(const saki::string_base<T, N>& str1, const saki::string_base<T, N>& str2)
	{
		return !(str1 == str2);
	}
}
#endif //SAKI_STRING_BASE_STRING_BASE_2019_01_22