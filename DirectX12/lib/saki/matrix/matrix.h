/**
* @file matrix.h
* @brief 行列
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_MATRIX_MATRIX_2018_12_13
#define SAKI_MATRIX_MATRIX_2018_12_13
#include <cstddef>
#include <type_traits>
#include <saki/matrix/details/matrix_operator.h>
#include <saki/matrix/details/matrix_math.h>
#include <saki/macro/type_macro.h>
#include <saki/vector/vector_4d.h>
#include <saki/array/array.h>

namespace saki
{
	/**
	* @brief 行列
	*/
	template<typename T>
	class matrix
	{
	public:
		SAKI_TYPE_MACRO(T)
	private:
		saki::array<saki::array<value_type, 4>, 4> m;
	public:
		/**
		* @brief 引数なしコンストラクタ
		* @details Identity初期化
		*/
		constexpr matrix() :
			m(
				saki::array<value_type, 4>(value_type(1), value_type(0), value_type(0), value_type(0)),
				saki::array<value_type, 4>(value_type(0), value_type(1), value_type(0), value_type(0)),
				saki::array<value_type, 4>(value_type(0), value_type(0), value_type(1), value_type(0)),
				saki::array<value_type, 4>(value_type(0), value_type(0), value_type(0), value_type(1))
			)
		{}
		/**
		* @brief 引数ありコンストラクタ
		*/
		constexpr matrix(
			const_reference m00, const_reference m01, const_reference m02, const_reference m03,
			const_reference m10, const_reference m11, const_reference m12, const_reference m13,
			const_reference m20, const_reference m21, const_reference m22, const_reference m23,
			const_reference m30, const_reference m31, const_reference m32, const_reference m33) :
			m(
				saki::array<value_type, 4>(m00, m01, m02, m03),
				saki::array<value_type, 4>(m10, m11, m12, m13),
				saki::array<value_type, 4>(m20, m21, m22, m23),
				saki::array<value_type, 4>(m30, m31, m32, m33))

		{}
		/**
		* @brief 生配列からの初期化
		* @param arr 4*4の配列
		*/
		template<typename U>
		explicit constexpr matrix(const U arr[4][4]) :
			m(
				saki::array<value_type, 4>
				(static_cast<value_type>(arr[0][0]), static_cast<value_type>(arr[0][1]),
					static_cast<value_type>(arr[0][2]), static_cast<value_type>(arr[0][3])),
				saki::array<value_type, 4>(
					static_cast<value_type>(arr[1][0]), static_cast<value_type>(arr[1][1]),
					static_cast<value_type>(arr[1][2]), static_cast<value_type>(arr[1][3])),
				saki::array<value_type, 4>(
					static_cast<value_type>(arr[2][0]), static_cast<value_type>(arr[2][1]),
					static_cast<value_type>(arr[2][2]), static_cast<value_type>(arr[2][3])),
				saki::array<value_type, 4>(
					static_cast<value_type>(arr[3][0]), static_cast<value_type>(arr[3][1]),
					static_cast<value_type>(arr[3][2]), static_cast<value_type>(arr[3][3]))
			)
		{}
		/**
		* @brief vector4での初期化
		* @param v1 1行目
		* @param v2 2行目
		* @param v3 3行目
		* @param v4 4行目
		*/
		template<typename U1, typename U2, typename U3, typename U4>
		constexpr matrix(const saki::vector4<U1>& v1, const saki::vector4<U2>& v2,
			const saki::vector4<U3>& v3, const saki::vector4<U4>& v4) :
			m(
				saki::array<value_type, 4>(
					static_cast<value_type>(v1.x), static_cast<value_type>(v1.y),
					static_cast<value_type>(v1.z), static_cast<value_type>(v1.w)),
				saki::array<value_type, 4>(
					static_cast<value_type>(v2.x), static_cast<value_type>(v2.y),
					static_cast<value_type>(v2.z), static_cast<value_type>(v2.w)),
				saki::array<value_type, 4>(
					static_cast<value_type>(v3.x), static_cast<value_type>(v3.y),
					static_cast<value_type>(v3.z), static_cast<value_type>(v3.w)),
				saki::array<value_type, 4>(
					static_cast<value_type>(v4.x), static_cast<value_type>(v4.y),
					static_cast<value_type>(v4.z), static_cast<value_type>(v4.w))
			)
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		matrix(const matrix<value_type>&) = default;
		matrix<value_type>& operator=(const matrix<value_type>&) = default;
		matrix(matrix<value_type>&&)noexcept = default;
		matrix<value_type>& operator=(matrix<value_type>&&)noexcept = default;
		/**
		* @brief +=演算子
		*/
		template<typename U = value_type>
		auto operator+=(const saki::matrix<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = value_type>
		auto operator-=(const saki::matrix<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=演算子(スカラ)
		*/
		template<typename U = value_type>
		auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief *=演算子(行列)
		*/
		template<typename U = value_type>
		auto operator*=(const saki::matrix<U>& other)
		{
			*this = *this * other;
			return *this;
		}
		/**
		* @brief /=演算子(スカラ)
		*/
		template<typename U = value_type>
		auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief 単項+演算子
		*/
		constexpr saki::matrix<value_type> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr saki::matrix<value_type> operator-()const
		{
			return saki::matrix<value_type>{
				m[0][0] * -1, m[0][1] * -1,
					m[0][2] * -1, m[0][3] * -1,
					m[1][0] * -1, m[1][1] * -1,
					m[1][2] * -1, m[1][3] * -1,
					m[2][0] * -1, m[2][1] * -1,
					m[2][2] * -1, m[2][3] * -1,
					m[3][0] * -1, m[3][1] * -1,
					m[3][2] * -1, m[3][3] * -1,
			};
		}
		/**
		* @brief []演算子
		*/
		constexpr saki::array<value_type, 4>& operator[](const size_t index)
		{
			return m[index];
		}
		/**
		* @brief []演算子(constexpr)
		*/
		constexpr const saki::array<value_type, 4>& operator[](const size_t index)const
		{
			return m[index];
		}
		/**
		* @brief 単位行列に変換
		*/
		void identity()
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					m[i][j] = (i == j) ? 1 : 0;
				}
			}
		}
		/**
		* @brief 転置行列に変換
		*/
		void transpose()
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = i + 1; j < 4; ++j)
				{
					value_type temp = m[i][j];
					m[i][j] = m[j][i];
					m[j][i] = temp;
				}
			}
		}
	};

	/**
	* @brief 単位行列
	*/
	template<typename T>
	static constexpr saki::matrix<T> matrix_identity{
		static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) ,
		static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) ,
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0) ,
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
	};
}
#endif //SAKI_MATRIX_MATRIX_2018_12_13