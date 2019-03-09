/**
* @file addition.h
* @brief 足し算のオペレーターを呼び出すconstexpr関数オブジェクト
* @author 石山 悠
* @date 2018/12/08
*/
#pragma once
#ifndef SAKI_FUNCTION_OBJECT_ADDITION_2018_12_08
#define SAKI_FUNCTION_OBJECT_ADDITION_2018_12_08

namespace saki
{
	/**
	* @brief 足し算のconstexpr対応した関数オブジェクト
	*/
	struct addition
	{
		template<typename T1, typename T2>
		constexpr auto operator()(const T1& t1, const T2& t2)const
			->decltype(t1 + t2)
		{
			return t1 + t2;
		}
	};
}
#endif //SAKI_FUNCTION_OBJECT_ADDITION_2018_12_08