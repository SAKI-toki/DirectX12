/**
* @file matrix_operator.h
* @brief matrix�N���X�̉��Z�q
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_MATRIX_DETAILS_MATRIX_OPERATOR_2018_12_13
#define SAKI_MATRIX_DETAILS_MATRIX_OPERATOR_2018_12_13
#include <utility>
#include <saki/function_object.h>

namespace saki
{
	//�v���g�^�C�v�錾
	template<typename T>
	class matrix;
	namespace details
	{
		/**
		* @brief �s�񓯎m�̉��Z(+��-)
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto matrix_matrix_some_operator(const matrix<T1>& m1, const matrix<T2>& m2, const Func& f)
		{
			return matrix<decltype(std::declval<T1>() * std::declval<T2>())>
			{
				f(m1[0][0], m2[0][0]), f(m1[0][1], m2[0][1]),
					f(m1[0][2], m2[0][2]), f(m1[0][3], m2[0][3]),
					f(m1[1][0], m2[1][0]), f(m1[1][1], m2[1][1]),
					f(m1[1][2], m2[1][2]), f(m1[1][3], m2[1][3]),
					f(m1[2][0], m2[2][0]), f(m1[2][1], m2[2][1]),
					f(m1[2][2], m2[2][2]), f(m1[2][3], m2[2][3]),
					f(m1[3][0], m2[3][0]), f(m1[3][1], m2[3][1]),
					f(m1[3][2], m2[3][2]), f(m1[3][3], m2[3][3])
			};
		}
		/**
		* @brief �s��ƃX�J���̉��Z
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto matrix_scalar_some_operator(const matrix<T1>& m, const T2& scalar, const Func& f)
		{
			return matrix<decltype(std::declval<T1>() * std::declval<T2>())>
			{
				f(m[0][0], scalar), f(m[0][1], scalar),
					f(m[0][2], scalar), f(m[0][3], scalar),
					f(m[1][0], scalar), f(m[1][1], scalar),
					f(m[1][2], scalar), f(m[1][3], scalar),
					f(m[2][0], scalar), f(m[2][1], scalar),
					f(m[2][2], scalar), f(m[2][3], scalar),
					f(m[3][0], scalar), f(m[3][1], scalar),
					f(m[3][2], scalar), f(m[3][3], scalar)
			};
		}
	}
	/**
	* @brief +���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator+(const matrix<T1>& m1, const matrix<T2>& m2)
	{
		return details::matrix_matrix_some_operator(m1, m2, saki::addition());
	}
	/**
	* @brief -���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator-(const matrix<T1>& m1, const matrix<T2>& m2)
	{
		return details::matrix_matrix_some_operator(m1, m2, saki::subtraction());
	}
	/**
	* @brief *���Z�q(�s��*�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const matrix<T1>& m, const T2& scalar)
	{
		return details::matrix_scalar_some_operator(m, scalar, saki::multiplication());
	}
	/**
	* @brief *���Z�q(�X�J��*�s��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const T1& scalar, const matrix<T2>& m)
	{
		return m * scalar;
	}
	/**
	* @brief *���Z�q(�s��*�s��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const matrix<T1>& m1, const matrix<T2>& m2)
	{
		using m_type = decltype(std::declval<T1>() * std::declval<T2>());
		matrix<m_type> mat;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m_type sum = 0;
				for (int k = 0; k < 4; ++k)
				{
					sum += m1[i][k] * m2[k][j];
				}
				mat[i][j] = sum;
			}
		}
		return mat;
	}
	/**
	* @brief /���Z�q(�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const matrix<T1>& m, const T2& scalar)
	{
		return details::matrix_scalar_some_operator(m, scalar, saki::division());
	}
	/**
	* @brief ==���Z�q
	*/
	template<typename T>
	constexpr bool operator==(const matrix<T>& m1, const matrix<T>& m2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (m1[i][j] != m2[i][j]) { return false; }
			}
		}
		return true;
	}
	/**
	* @brief !=���Z�q
	*/
	template<typename T>
	constexpr bool operator!=(const matrix<T>& m1, const matrix<T>& m2)
	{
		return !(m1 == m2);
	}
	/**
	* @brief ==���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator==(const matrix<T1>& m1, const matrix<T2>& m2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (m1[i][j] != m2[i][j]) { return false; }
			}
		}
		return true;
	}
	/**
	* @brief !=���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator!=(const matrix<T1>& m1, const matrix<T2>& m2)
	{
		return !(m1 == m2);
	}
}
#endif //SAKI_MATRIX_DETAILS_MATRIX_OPERATOR_2018_12_13