/**
* @file has_check_method.h
* @brief �w�肵���^��check�֐��������Ă��邩�ǂ������肷�郁�^�֐�
* @author �ΎR �I
* @date 2018/12/23
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_HAS_CHECK_METHOD_2018_12_23
#define SAKI_TYPE_TRAITS_HAS_CHECK_METHOD_2018_12_23
#include <type_traits>
#include <utility>

namespace saki
{
	/**
	* @brief check�֐��������Ă��邩�ǂ����𔻒肷��\����
	*/
	template<typename T>
	struct has_check
	{
	private:
		template<typename U>
		static constexpr std::true_type check_check(decltype(std::declval<U>().check(char()))* u);
		template<typename U>
		static constexpr std::false_type check_check(...);
	public:
		static constexpr auto value = decltype(check_check<T>(nullptr))::value;
	};
	/**
	* @brief has_check���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto has_check_v = saki::has_check<T>::value;
}
#endif //SAKI_TYPE_TRAITS_HAS_CHECK_METHOD_2018_12_23