/**
* @file vector_4d_operator.h
* @brief vector4�N���X�̉��Z�q
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_VECTOR_DETAILS_4D_VECTOR_4D_OPERATOR_2018_12_13
#define SAKI_VECTOR_DETAILS_4D_VECTOR_4D_OPERATOR_2018_12_13
#include <utility>
#include <saki/function_object.h>
#include <type_traits>

namespace saki
{
	template<typename T>
	class vector4;
	namespace details
	{
		/**
		* @brief �x�N�g�����m�̉��Z
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto vector4_vector4_some_operator(const vector4<T1>& v1, const vector4<T2>& v2, Func&& f)
		{
			return vector4<decltype(std::declval<T1>() + std::declval<T2>())>
			{ f(v1.x, v2.x), f(v1.y, v2.y), f(v1.z, v2.z), f(v1.w, v2.w) };
		}
		/**
		* @brief �x�N�g���ƃX�J���̉��Z
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto vector4_scalar_some_operator(const vector4<T1>& v, const T2& scalar, Func&& f)
		{
			return vector4<decltype(std::declval<T1>() * std::declval<T2>())>
			{  f(v.x, scalar), f(v.y, scalar), f(v.z, scalar), f(v.w, scalar)  };
		}
	}
	/**
	* @brief +���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator+(const vector4<T1>& v1, const vector4<T2>& v2)
	{
		return details::vector4_vector4_some_operator(v1, v2, saki::addition());
	}
	/**
	* @brief -���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator-(const vector4<T1>& v1, const vector4<T2>& v2)
	{
		return details::vector4_vector4_some_operator(v1, v2, saki::subtraction());
	}
	/**
	* @brief *���Z�q(�x�N�g��*�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const vector4<T1>& v, const T2& scalar)
	{
		return details::vector4_scalar_some_operator(v, scalar, saki::multiplication());
	}
	/**
	* @brief *���Z�q(�X�J��*�x�N�g��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const T1& scalar, const vector4<T2>& v)
	{
		return v + scalar;
	}
	/**
	* @brief *���Z�q(�x�N�g��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const vector4<T1>& v1, const vector4<T2>& v2)
	{
		return details::vector4_vector4_some_operator(v1, v2, saki::multiplication());
	}
	/**
	* @brief /���Z�q(�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const vector4<T1>& v, const T2& scalar)
	{
		return details::vector4_scalar_some_operator(v, scalar, saki::division());
	}
	/**
	* @brief /���Z�q(�x�N�g��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const vector4<T1>& v1, const vector4<T2>& v2)
	{
		return details::vector4_vector4_some_operator(v1, v2, saki::division());
	}
	/**
	* @brief ==���Z�q
	*/
	template<typename T>
	constexpr bool operator==(const vector4<T>& v1, const vector4<T>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
	}
	/**
	* @brief !=���Z�q
	*/
	template<typename T>
	constexpr bool operator!=(const vector4<T>& v1, const vector4<T>& v2)
	{
		return !(v1 == v2);
	}
	/**
	* @brief ==���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator==(const vector4<T1>& v1, const vector4<T2>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w;
	}
	/**
	* @brief !=���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator!=(const vector4<T1>& v1, const vector4<T2>& v2)
	{
		return !(v1 == v2);
	}
}
#endif //SAKI_VECTOR_DETAILS_4D_VECTOR_4D_OPERATOR_2018_12_13