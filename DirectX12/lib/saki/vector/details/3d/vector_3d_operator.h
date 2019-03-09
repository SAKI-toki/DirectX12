/**
* @file vector_3d_operator.h
* @brief vector3クラスの演算子
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_VECTOR_DETAILS_3D_VECTOR_3D_OPERATOR_2018_12_13
#define SAKI_VECTOR_DETAILS_3D_VECTOR_3D_OPERATOR_2018_12_13
#include <utility>
#include <saki/function_object.h>
#include <type_traits>

namespace saki
{
	template<typename T>
	class vector3;
	namespace details
	{
		/**
		* @brief ベクトル同士の演算
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto vector3_vector3_some_operator(const vector3<T1>& v1, const vector3<T2>& v2, Func&& f)
		{
			return vector3<decltype(std::declval<T1>() + std::declval<T2>())>
			{ f(v1.x, v2.x), f(v1.y, v2.y), f(v1.z, v2.z) };
		}
		/**
		* @brief ベクトルとスカラの演算
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto vector3_scalar_some_operator(const vector3<T1>& v, const T2& scalar, Func&& f)
		{
			return vector3<decltype(std::declval<T1>() * std::declval<T2>())>
			{  f(v.x, scalar), f(v.y, scalar), f(v.z, scalar)  };
		}
	}
	/**
	* @brief +演算子
	*/
	template<typename T1, typename T2>
	constexpr auto operator+(const vector3<T1>& v1, const vector3<T2>& v2)
	{
		return details::vector3_vector3_some_operator(v1, v2, saki::addition());
	}
	/**
	* @brief -演算子
	*/
	template<typename T1, typename T2>
	constexpr auto operator-(const vector3<T1>& v1, const vector3<T2>& v2)
	{
		return details::vector3_vector3_some_operator(v1, v2, saki::subtraction());
	}
	/**
	* @brief *演算子(ベクトル*スカラ)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const vector3<T1>& v, const T2& scalar)
	{
		return details::vector3_scalar_some_operator(v, scalar, saki::multiplication());
	}
	/**
	* @brief *演算子(スカラ*ベクトル)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const T1& scalar, const vector3<T2>& v)
	{
		return v + scalar;
	}
	/**
	* @brief *演算子(ベクトル)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const vector3<T1>& v1, const vector3<T2>& v2)
	{
		return details::vector3_vector3_some_operator(v1, v2, saki::multiplication());
	}
	/**
	* @brief /演算子(スカラ)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const vector3<T1>& v, const T2& scalar)
	{
		return details::vector3_scalar_some_operator(v, scalar, saki::division());
	}
	/**
	* @brief /演算子(ベクトル)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const vector3<T1>& v1, const vector3<T2>& v2)
	{
		return details::vector3_vector3_some_operator(v1, v2, saki::division());
	}
	/**
	* @brief ==演算子
	*/
	template<typename T>
	constexpr bool operator==(const vector3<T>& v1, const vector3<T>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}
	/**
	* @brief !=演算子
	*/
	template<typename T>
	constexpr bool operator!=(const vector3<T>& v1, const vector3<T>& v2)
	{
		return !(v1 == v2);
	}
	/**
	* @brief ==演算子(型不一致)
	* @details この関数の使用は推奨しない
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator==(const vector3<T1>& v1, const vector3<T2>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}
	/**
	* @brief !=演算子(型不一致)
	* @details この関数の使用は推奨しない
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator!=(const vector3<T1>& v1, const vector3<T2>& v2)
	{
		return !(v1 == v2);
	}
}
#endif //SAKI_VECTOR_DETAILS_3D_VECTOR_3D_OPERATOR_2018_12_13