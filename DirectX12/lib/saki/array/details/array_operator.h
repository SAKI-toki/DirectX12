/**
* @file array_operator.h
* @brief 配列クラスの演算子
* @author 石山 悠
* @date 2018/12/24
*/
#pragma once
#ifndef SAKI_ARRAY_DETAILS_ARRAY_OPERATOR_2018_12_24
#define SAKI_ARRAY_DETAILS_ARRAY_OPERATOR_2018_12_24
#include <cstddef>

namespace saki
{
	//プロトタイプ宣言
	template<typename T, size_t Size>
	class array;
	/**
	* @brief ==演算子
	*/
	template<typename T, size_t Size>
	constexpr bool operator==(const array<T, Size>& arr1, const array<T, Size>& arr2)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			if (arr1[i] != arr2[i])return false;
		}
		return true;
	}
	/**
	* @brief !=演算子
	*/
	template<typename T, size_t Size>
	constexpr bool operator!=(const array<T, Size>& arr1, const array<T, Size>& arr2)
	{
		return !(arr1 == arr2);
	}
}
#endif //SAKI_ARRAY_DETAILS_ARRAY_OPERATOR_2018_12_24