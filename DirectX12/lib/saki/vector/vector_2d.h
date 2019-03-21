/**
* @file vector_2d.h
* @brief 2次元でのベクトル
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_VECTOR_VECTOR_2D_2018_12_13
#define SAKI_VECTOR_VECTOR_2D_2018_12_13
#include <limits> //for numeric_limits
#include <saki/math/sqrt.h> //for constexpr_sqrt
#include <saki/vector/details/2d/vector_2d_operator.h>
#include <saki/macro/type_macro.h>
#include <cmath>


namespace saki
{
	/**
	* @brief 2次元でのベクトル
	*/
	template<typename T>
	class vector2
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		value_type 
			x = static_cast<value_type>(0),
			y = static_cast<value_type>(0);
		/**
		* @brief 引数なしコンストラクタ
		* @details 全て0で初期化
		*/
		constexpr vector2()
		{}
		/**
		* @brief 引数ありコンストラクタ
		* @param _x xの初期値
		* @param _y yの初期値
		*/
		constexpr vector2(const_reference _x, const_reference _y) :
			x(_x), y(_y)
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		vector2(const vector2<value_type>&) = default;
		vector2<value_type>& operator=(const vector2<value_type>&) = default;
		vector2(vector2<value_type>&&)noexcept = default;
		vector2<value_type>& operator=(vector2<value_type>&&)noexcept = default;
		/**
		* @brief +=演算子
		*/
		template<typename U = value_type>
		constexpr auto operator+=(const saki::vector2<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = value_type>
		constexpr auto operator-=(const saki::vector2<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=演算子(スカラ)
		*/
		template<typename U = value_type>
		constexpr auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief *=演算子(ベクトル)
		*/
		template<typename U = value_type>
		constexpr auto operator*=(const saki::vector2<U>& other)
		{
			*this = *this * other;
			return *this;
		}
		/**
		* @brief /=演算子(スカラ)
		*/
		template<typename U = value_type>
		constexpr auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief /=演算子(ベクトル)
		*/
		template<typename U = value_type>
		constexpr auto operator/=(const saki::vector2<U>& other)
		{
			*this = *this / other;
			return *this;
		}
		/**
		* @brief 単項+演算子
		*/
		constexpr saki::vector2<value_type> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr saki::vector2<value_type> operator-()const
		{
			return saki::vector2<value_type>(this->x * (-1), this->y * (-1));
		}
		/**
		* @brief []演算子
		*/
		constexpr reference operator[](const size_type index)
		{
			return (index == 0) ? this->x : this->y;
		}
		/**
		* @brief []演算子(constexpr)
		*/
		constexpr const_reference operator[](const size_type index)const
		{
			return (index == 0) ? this->x : this->y;
		}
		/**
		* @brief ++演算子(前置)
		*/
		constexpr saki::vector2<value_type>& operator++()
		{
			this->x += 1; this->y += 1;
			return *this;
		}
		/**
		* @brief ++演算子(後置)
		*/
		constexpr saki::vector2<value_type> operator++(int)
		{
			saki::vector2<value_type> temp = *this;
			this->x += 1; this->y += 1;
			return temp;
		}
		/**
		* @brief --演算子(前置)
		*/
		constexpr saki::vector2<value_type>& operator--()
		{
			this->x -= 1; this->y -= 1;
			return *this;
		}
		/**
		* @brief --演算子(後置)
		*/
		constexpr saki::vector2<value_type> operator--(int)
		{
			saki::vector2<value_type> temp = *this;
			this->x -= 1; this->y -= 1;
			return temp;
		}
		/**
		* @brief 正規化
		* @details int型の場合、すべての要素が0で帰ります
		*/
		constexpr void normalize()
		{
			//分母
			auto den = std::sqrt(this->x * this->x + this->y * this->y);
			if (den == 0)
			{
				this->x = 0;
				this->y = 0;
			}
			else
			{
				this->x /= den;
				this->y /= den;
			}
		}

	};
	/**
	* @brief vector2のオールゼロ
	*/
	template<typename T>
	static constexpr saki::vector2<T> vector2_zero{ static_cast<T>(0), static_cast<T>(0) };
	/**
	* @brief vector2のオールワン
	*/
	template<typename T>
	static constexpr saki::vector2<T> vector2_one{ static_cast<T>(1), static_cast<T>(1) };
	/**
	* @brief vector2の最小値
	*/
	template<typename T>
	static constexpr saki::vector2<T> vector2_min{ std::numeric_limits<T>::min(), std::numeric_limits<T>::min() };
	/**
	* @brief vector2の最大値
	*/
	template<typename T>
	static constexpr saki::vector2<T> vector2_max{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };
	/**
	* @brief 正規化
	* @return 正規化したもの
	*/
	template<typename U = double, typename T>
	constexpr saki::vector2<U> normalize(const saki::vector2<T>& v)
	{
		//分母
		auto den = saki::sqrt(v.x * v.x + v.y * v.y);
		if (den == 0)
		{
			return saki::vector2<U>
				(static_cast<U>(0),//x
					static_cast<U>(0));//y
		}
		else
		{
			return saki::vector2<U>
				(static_cast<U>(v.x / den),//x
					static_cast<U>(v.y / den));//y
		}
	}
	/**
	* @brief 内積
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U dot(const saki::vector2<T1>& v1, const saki::vector2<T2>& v2)
	{
		return static_cast<U>(v1.x * v2.x + v1.y * v2.y);
	}
	/**
	* @brief 外積
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U cross(const saki::vector2<T1>& v1, const saki::vector2<T2>& v2)
	{
		return static_cast<U>(v1.x * v2.y - v1.y * v2.x);
	}

	/**
	* @brief 線形補間
	* @details Quaternionは使用していません
	*/
	template<typename U = double, typename T1, typename T2, typename T = double>
	constexpr saki::vector2<U> lerp(const saki::vector2<T1>& v1, const saki::vector2<T2>& v2, const T& t, const T& base = 1)
	{
		auto ratio = t / base;
		return saki::vector2<U>(
			v1.x + (v2.x - v1.x) * ratio,
			v1.y + (v2.y - v1.y) * ratio);
	}
}
#endif //SAKI_VECTOR_VECTOR_2D_2018_12_13