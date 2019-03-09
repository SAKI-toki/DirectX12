/**
* @file has_y.h
* @brief �w�肵���^���ϐ�y�������Ă��邩�ǂ������肷�郁�^�֐�
* @author �ΎR �I
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Y_2019_01_22
#define SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Y_2019_01_22
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief �ϐ�y�������Ă��邩�ǂ����𔻒肷��\����
	*/
	template<typename T>
	struct has_y
	{
	private:
		template<typename U>
		static constexpr std::true_type y_check(saki::remove_reference_const_t<decltype(std::declval<U>().y)>*);
		template<typename U>
		static constexpr std::false_type y_check(...);
	public:
		static constexpr auto value = decltype(y_check<T>(nullptr))::value;
	};
	/**
	* @brief has_y���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto has_y_v = saki::has_y<T>::value;
}
#endif //SAKI_TYPE_TRAITS_HAS_VARIABLE_HAS_Y_2019_01_22