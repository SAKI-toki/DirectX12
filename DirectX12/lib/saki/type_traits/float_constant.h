/**
* @file float_constant.h
* @brief ���������_�^�̒萔��\���^
* @author �ΎR �I
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_FLOAT_CONSTANT_2019_01_15
#define SAKI_TYPE_TRAITS_FLOAT_CONSTANT_2019_01_15
#include <cstddef>
#include <saki/math/digit_count.h>
#include <saki/math/details/pow_n.h>
#include <saki/math/copysign.h>

namespace saki
{
	namespace details
	{
		/**
		* @brief ���������_�^�̒萔��\���x�[�X�N���X
		*/
		template<typename T,int Integer, size_t Dec, size_t ZeroNum = 0>
		struct float_constant_base
		{
			static constexpr T value = Integer +
				saki::copysign(static_cast<T>(Dec) / 
					saki::details::pow_n(static_cast<T>(10), ZeroNum + saki::digit_count(Dec)),
					Integer);
			constexpr operator T()const
			{
				return value;
			}
			constexpr T operator()()const
			{
				return value;
			}
		};
	}
	/**
	* @brief ���������_�^�̒萔��\��
	*/
	template<int Integer, size_t Dec, size_t ZeroNum = 0>
	struct float_constant :public saki::details::float_constant_base<float, Integer, Dec, ZeroNum>
	{};
	/**
	* @brief float_constant���ȒP�ɌĂяo����ϐ�
	*/
	template<int Integer, size_t Dec, size_t ZeroNum = 0>
	static constexpr float float_constant_v = saki::float_constant<Integer, Dec, ZeroNum>::value;

	/**
	* @brief �{���x���������_�^�̒萔��\��
	*/
	template<int Integer, size_t Dec, size_t ZeroNum = 0>
	struct double_constant :public saki::details::float_constant_base<double, Integer, Dec, ZeroNum>
	{};
	/**
	* @brief double_constant���ȒP�ɌĂяo����ϐ�
	*/
	template<int Integer, size_t Dec, size_t ZeroNum = 0>
	static constexpr double double_constant_v = saki::double_constant<Integer, Dec, ZeroNum>::value;
}
#endif //SAKI_TYPE_TRAITS_FLOAT_CONSTANT_2019_01_15