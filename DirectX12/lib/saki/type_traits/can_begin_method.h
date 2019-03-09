/**
* @file can_begin_method.h
* @brief �w�肵���^��std::begin�ł��邩�ǂ������肷�郁�^�֐�
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_BEGIN_METHOD_2018_12_13
#define SAKI_TYPE_TRAITS_BEGIN_METHOD_2018_12_13
#include <type_traits>
#include <utility>
#include <iterator>
namespace saki
{
	/**
	* @brief begin�ł��邩�ǂ����𔻒肷��\����
	*/
	template<typename T>
	struct can_begin
	{
	private:
		template<typename U>
		static constexpr std::true_type begin_check(decltype(std::begin(std::declval<U>()))* u);
		template<typename U>
		static constexpr std::false_type begin_check(...);
	public:
		static constexpr auto value = decltype(begin_check<T>(nullptr))::value;
	};
	/**
	* @brief can_begin���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto can_begin_v = saki::can_begin<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_BEGIN_METHOD_2018_12_13