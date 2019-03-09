/**
* @file distance.h
* @brief 2点間の距離を測る
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_MATH_DISTANCE_2019_01_22
#define SAKI_MATH_DISTANCE_2019_01_22
#include <type_traits>
#include <saki/math/hypot.h>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/type_traits/has_variable/has_x.h>
#include <saki/type_traits/has_variable/has_y.h>
#include <saki/type_traits/has_variable/has_z.h>

namespace saki
{
	/**
	* @brief 二点間の距離(XY)
	*/
	template<typename T1, typename T2,
		typename saki::enable_if_nullptr_t <
		saki::has_x_v<T1> && saki::has_x_v<T2> &&
		saki::has_y_v<T1> && saki::has_y_v<T2>
	> = nullptr>
		constexpr auto distanceXY(const T1& v1, const T2& v2)
	{
		return saki::hypot(
			(v1.x - v2.x),
			(v1.y - v2.y));
	}
	/**
	* @brief 二点間の距離(XZ)
	*/
	template<typename T1, typename T2,
		typename saki::enable_if_nullptr_t <
		saki::has_x_v<T1> && saki::has_x_v<T2> &&
		saki::has_z_v<T1> && saki::has_z_v<T2>
	> = nullptr>
	constexpr auto distanceXZ(const T1& v1, const T2& v2)
	{
		return saki::hypot(
			(v1.x - v2.x),
			(v1.z - v2.z));
	}
	/**
	* @brief 二点間の距離(YZ)
	*/
	template<typename T1, typename T2,
		typename saki::enable_if_nullptr_t <
		saki::has_y_v<T1> && saki::has_y_v<T2> &&
		saki::has_z_v<T1> && saki::has_z_v<T2>
	> = nullptr>
	constexpr auto distanceYZ(const T1& v1, const T2& v2)
	{
		return saki::hypot(
			(v1.y - v2.y),
			(v1.z - v2.z));
	}
	/**
	* @brief 二点間の距離(XYZ)
	*/
	template<typename T1, typename T2,
		typename saki::enable_if_nullptr_t <
		saki::has_x_v<T1> && saki::has_x_v<T2> &&
		saki::has_y_v<T1> && saki::has_y_v<T2> &&
		saki::has_z_v<T1> && saki::has_z_v<T2>
	> = nullptr>
	constexpr auto distanceXYZ(const T1& v1, const T2& v2)
	{
		return saki::hypot(
			(v1.x - v2.x),
			(v1.y - v2.y),
			(v1.z - v2.z));
	}
}
#endif //SAKI_MATH_DISTANCE_2019_01_22