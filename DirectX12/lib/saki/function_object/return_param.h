/**
* @file return_param.h
* @brief ���̂܂܈����̒l��Ԃ��֐��I�u�W�F�N�g
* @author �ΎR �I
* @date 2018/12/10
*/
#pragma once
#ifndef SAKI_FUNCTION_OBJECT_RETURN_PARAM_2018_12_10
#define SAKI_FUNCTION_OBJECT_RETURN_PARAM_2018_12_10

namespace saki
{
	/**
	* @brief ���̂܂܈�����Ԃ��֐��I�u�W�F�N�g
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