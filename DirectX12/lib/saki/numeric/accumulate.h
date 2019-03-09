/**
* @file accumulate.h
* @brief ������accumulate�֐��̊ȗ���
* @author �ΎR �I
* @date 2019/01/15
*/
/*
�S�Ă̗v�f�����v�i���͎w�肵�����Z�q�j���R���e�i�N���X�Ə����l��n�������ŉ\�ɂ���
�W�����C�u�����ł�Iterator��n���̂ŁA�S�ĂȂ炱�������g�����ق����ǂ�
*/
#pragma once
#ifndef SAKI_NUMERIC_ACCUMULATE_2019_01_15
#define SAKI_NUMERIC_ACCUMULATE_2019_01_15
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/type_traits/can_range_based_for.h>
#include <saki/type_traits/remove_reference_const.h>
#include <saki/function_object/addition.h>
namespace saki
{
	/**
	* @brief ������2�̊֐����w�肵�A��������ׂĂ̗v�f�ŉ�
	* @param con �R���e�i�N���X
	* @param init �����l
	* @param binary_op ������2�̊֐�
	* @return �S�Ă̗v�f���񂵂�����
	*/
	template<typename Container, typename BinaryOperation = saki::addition,
		typename T = saki::remove_reference_const_t<typename Container::value_type>,
		typename saki::enable_if_nullptr_t<
		saki::can_range_based_for_v<Container>&&		//�R���e�i��begin,end�L�����ǂ���
		std::is_invocable_r_v<T,BinaryOperation, T, T>	//BinaryOperation(T,T)�̕Ԃ�l��T���ǂ���
	> = nullptr>
		constexpr T accumulate(const Container& con, T init = 0, BinaryOperation&& binary_op = saki::addition())
	{
		for (const auto& n : con)
		{
			init = static_cast<T>(binary_op(init, n));
		}
		return init;
	}
}
#endif //SAKI_NUMERIC_ACCUMULATE_2019_01_15