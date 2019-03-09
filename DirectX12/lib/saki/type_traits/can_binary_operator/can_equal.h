/**
* @file can_equal_equal.h
* @brief �w�肵���^��(=)���Z�q���g�p�ł��邩�ǂ������肷�郁�^�֐�
* @author �ΎR �I
* @date 2019/01/24
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_CAN_BINARY_OPERATOR_CAN_EQUAL_2019_01_24
#define SAKI_TYPE_TRAITS_CAN_BINARY_OPERATOR_CAN_EQUAL_2019_01_24
#include <type_traits>
#include <utility>
#include <saki/type_traits/remove_reference_const.h>

namespace saki
{
	/**
	* @brief ������Z�q���`���Ă��邩�ǂ����𔻒肷��\����(�����^���m)
	*/
	template<typename T>
	struct can_same_equal
	{
	private:
		template<typename U>
		static constexpr std::true_type same_equal_check(
			saki::remove_reference_const_t<
			decltype(std::declval<std::add_lvalue_reference_t<decltype(std::declval<U>())>>() = std::declval<U>())>*);
		template<typename U>
		static constexpr std::false_type same_equal_check(...);
	public:
		static constexpr auto value = decltype(same_equal_check<T>(nullptr))::value;
	};
	/**
	* @brief can_same_equal���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto can_same_equal_v = saki::can_same_equal<T>::value;
	/**
	* @brief ������Z�q���`���Ă��邩�ǂ����𔻒肷��\����(�Ⴄ�^���m)
	*/
	template<typename T1, typename T2>
	struct can_different_equal
	{
	private:
		template<typename U1,typename U2>
		static constexpr std::true_type different_equal_check(
			saki::remove_reference_const_t<
			decltype(std::declval<std::add_lvalue_reference_t<decltype(std::declval<U1>())>>() = std::declval<U2>())>*);
		template<typename U1, typename U2>
		static constexpr std::false_type different_equal_check(...);
	public:
		static constexpr auto value = decltype(different_equal_check<T1, T2>(nullptr))::value;
	};
	template<typename T>
	struct can_different_equal<T, T> :public saki::can_same_equal<T> {};
	/**
	* @brief can_different_equal���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T1, typename T2>
	static constexpr auto can_different_equal_v = saki::can_different_equal<T1, T2>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_BINARY_OPERATOR_CAN_EQUAL_2019_01_24