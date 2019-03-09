/**
* @file pow_n.h
* @brief ��������int�^��pow
* @author �ΎR �I
* @date 2019/01/19
*/
#pragma once
#ifndef SAKI_MATH_DETAILS_POW_N_2019_01_19
#define SAKI_MATH_DETAILS_POW_N_2019_01_19
#include <cstddef>
#include <type_traits>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	namespace details
	{
		/**
		* @brief pow����h��
		*/
		template<typename T1, typename T2,
			typename saki::enable_if_nullptr_t<std::is_integral_v<T2>> = nullptr>
		constexpr T1 pow_n(T1 x, T2 y)
		{
			T1 sum = static_cast<T1>(1);
			for (T2 i = 0; i < y; ++i)
			{
				sum *= x;
			}
			//�����t���̏ꍇ�̂݃}�C�i�X���l������
			if constexpr (std::is_signed_v<T2>)
			{
				for (T2 i = 0; i > y; --i)
				{
					sum /= x;
				}
			}
			return sum;
		}
	}
}
#endif //SAKI_MATH_DETAILS_POW_N_2019_01_19