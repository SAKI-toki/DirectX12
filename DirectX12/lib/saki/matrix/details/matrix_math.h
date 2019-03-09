/**
* @file matrix_math.h
* @brief çsóÒä÷åWÇÃåvéZä÷êî
* @author êŒéR óI
* @date 2018/12/29
*/
#pragma once
#ifndef SAKI_MATRIX_DETAILS_MATRIX_MATH_2018_12_29
#define SAKI_MATRIX_DETAILS_MATRIX_MATH_2018_12_29
#include <saki/vector/vector_2d.h>
#include <saki/vector/vector_3d.h>
#include <saki/vector/vector_4d.h>
#include <saki/math/sin.h>
#include <saki/math/cos.h>

namespace saki
{
	template<typename T>
	class matrix;
	/**
	* @brief ïΩçsà⁄ìÆ
	* @param vec à⁄ìÆó (vector2)
	*/
	template<typename T>
	constexpr matrix<T> translate(const saki::vector2<T>& vec)
	{
		return matrix<T>
		{
			1, 0, 0, vec.x,
				0, 1, 0, vec.y,
				0, 0, 1, 0,
				0, 0, 0, 1
		};
	}
	/**
	* @brief ïΩçsà⁄ìÆ
	* @param vec à⁄ìÆó (vector3)
	*/
	template<typename T>
	constexpr matrix<T> translate(const saki::vector3<T>& vec)
	{
		return matrix<T>
		{
			1, 0, 0, vec.x,
				0, 1, 0, vec.y,
				0, 0, 1, vec.z,
				0, 0, 0, 1
		};
	}
	/**
	* @brief ïΩçsà⁄ìÆ
	* @param vec à⁄ìÆó (vector4)
	*/
	template<typename T>
	constexpr matrix<T> translate(const saki::vector4<T>& vec)
	{
		return matrix<T>
		{
			1, 0, 0, vec.x,
				0, 1, 0, vec.y,
				0, 0, 1, vec.z,
				0, 0, 0, 1
		};
	}

	/**
	* @brief ägèk
	* @param vec ägèkó (vector2)
	*/
	template<typename T>
	constexpr matrix<T> scaling(const saki::vector2<T>& vec)
	{
		return matrix<T>
		{
			vec.x, 0, 0, 0,
				0, vec.y, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
		};
	}
	/**
	* @brief ägèk
	* @param vec ägèkó (vector3)
	*/
	template<typename T>
	constexpr matrix<T> scaling(const saki::vector3<T>& vec)
	{
		return matrix<T>
		{
			vec.x, 0, 0, 0,
				0, vec.y, 0, 0,
				0, 0, vec.z, 0,
				0, 0, 0, 1
		};
	}
	/**
	* @brief ägèk
	* @param vec ägèkó (vector4)
	*/
	template<typename T>
	constexpr matrix<T> scaling(const saki::vector4<T>& vec)
	{
		return matrix<T>
		{
			vec.x, 0, 0, 0,
				0, vec.y, 0, 0,
				0, 0, vec.z, 0,
				0, 0, 0, 1
		};
	}

	//template<typename T>
	//constexpr Matrix<T> rotateX(T angle)
	//{
	//	auto c = saki::cos(angle);
	//	auto s = saki::sin(angle);
	//	return Matrix<T>
	//	{
	//		c, -s, 0, 0,
	//			s, c, 0, 0,
	//			0, 0, 1, 0,
	//			0, 0, 0, 1
	//	};
	//}
	//template<typename T>
	//constexpr Matrix<T> rotateY(T angle)
	//{
	//	auto c = saki::cos(angle);
	//	auto s = saki::sin(angle);
	//	return Matrix<T>
	//	{
	//		c, 0, s, 0,
	//			0, 1, 0, 0,
	//			-s, 0, c, 0,
	//			0, 0, 0, 1
	//	};
	//}
	//template<typename T>
	//constexpr Matrix<T> rotateZ(T angle)
	//{
	//	auto c = saki::cos(angle);
	//	auto s = saki::sin(angle);
	//	return Matrix<T>
	//	{
	//		1, 0, 0, 0,
	//			0, c, -s, 0,
	//			0, s, c, 0,
	//			0, 0, 0, 1
	//	};
	//}
	//
	///**
	//* @brief âÒì]
	//* @param vec âÒì]ó (Vector3)
	//*/
	//template<typename T>
	//constexpr Matrix<T> rotate(const saki::Vector3<T>& vec)
	//{
	//	return rotateZ(vec.z)*rotateY(vec.y)*rotateX(vec.x);

	//	/*auto cx = saki::cos(vec.x);
	//	auto sx = saki::sin(vec.x);
	//	auto cy = saki::cos(vec.y);
	//	auto sy = saki::sin(vec.y);
	//	auto cz = saki::cos(vec.z);
	//	auto sz = saki::sin(vec.z);*/
	//}
	///**
	//* @brief âÒì]
	//* @param vec âÒì]ó (Vector4)
	//*/
	//template<typename T>
	//constexpr Matrix<T> rotate(const saki::Vector4<T>& vec)
	//{
	//	float x2 = vec.x + vec.x;
	//	float y2 = vec.y + vec.y;
	//	float z2 = vec.z + vec.z;

	//	float xx2 = vec.x * x2;
	//	float yy2 = vec.y * y2;
	//	float zz2 = vec.z * z2;
	//	float xy2 = vec.x * y2;
	//	float xz2 = vec.x * z2;
	//	float yz2 = vec.y * z2;
	//	float wx2 = vec.w * x2;
	//	float wy2 = vec.w * y2;
	//	float wz2 = vec.w * z2;

	//	return Matrix<T>
	//	{
	//		1 - yy2 - zz2, xy2 + wz2, xz2 - wy2, 0,
	//			xy2 - wz2, 1.0f - xx2 - zz2, yz2 + wx2, 0,
	//			xz2 + wy2, yz2 - wx2, 1.0f - xx2 - yy2, 0,
	//			0, 0, 0, 1
	//	};
	//}
}
#endif //SAKI_MATRIX_DETAILS_MATRIX_MATH_2018_12_29