/**
* @file return_param.h
* @brief そのまま引数の値を返す関数オブジェクト
* @author 石山 悠
* @date 2018/12/10
*/
#pragma once
#ifndef SAKI_FUNCTION_OBJECT_RETURN_PARAM_2018_12_10
#define SAKI_FUNCTION_OBJECT_RETURN_PARAM_2018_12_10

namespace saki
{
	/**
	* @brief そのまま引数を返す関数オブジェクト
	*/
	struct return_param
	{
		template<typename T>
		constexpr T operator()(const T& t)const
		{
			return t;
		}
	};
}
#endif //SAKI_FUNCTION_OBJECT_RETURN_PARAM_2018_12_10