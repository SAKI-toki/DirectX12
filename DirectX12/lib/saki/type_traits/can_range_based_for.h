/**
* @file can_range_based_for.h
* @brief �͈̓x�[�Xfor���ɗ��p�ł���^���ǂ������肷�郁�^�֐�
* @author �ΎR �I
* @date 2019/01/12
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_CAN_RANGE_BASED_FOR_2019_01_12
#define SAKI_TYPE_TRAITS_CAN_RANGE_BASED_FOR_2019_01_12
#include <type_traits>
#include <utility>
#include <saki/type_traits/can_begin_method.h>
#include <saki/type_traits/can_end_method.h>
#include <saki/type_traits/enable_if_nullptr.h>

namespace saki
{
	/**
	* @brief �͈̓x�[�Xfor���ɗ��p�ł���^���ǂ������肷��
	* @details std::begin��std::end�𗘗p�ł����true�Ƃ�������ɂȂ�
	*/
	template<typename T>
	class can_range_based_for
	{
		template<typename U,
			typename saki::enable_if_nullptr_t<saki::can_begin_v<U> && saki::can_end_v<U>> = nullptr>
			static constexpr std::true_type check_range_based_for(std::nullptr_t* u);
		template<typename U>
			static constexpr std::false_type check_range_based_for(...);
	public:
		static constexpr auto value = decltype(check_range_based_for<T>(nullptr))::value;
	};
	/**
	* @brief can_range_based_for���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto can_range_based_for_v = can_range_based_for<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_RANGE_BASED_FOR_2019_01_12