/**
* @file can_ostream.h
* @brief �w�肵���^��ostream���Z�q���I�[�o�[���[�h���Ă��邩�ǂ������肷��(���m�ɂ�cout)
* @author �ΎR �I
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_TYPE_TRAITS_CAN_OSTREAM_2019_01_22
#define SAKI_TYPE_TRAITS_CAN_OSTREAM_2019_01_22
#include <type_traits>
#include <utility>
#include <ostream>
#include <saki/type_traits/remove_reference_const.h>
namespace saki
{
	/**
	* @brief ostream���Z�q���I�[�o�[���[�h���Ă��邩�ǂ������肷��\����(cout)
	*/
	template<typename T>
	struct can_ostream
	{
	private:
		template<typename U>
		static constexpr std::true_type ostream_check(
			saki::remove_reference_const_t<decltype(std::cout << (std::declval<U>()))>* u);
		template<typename U>
		static constexpr std::false_type ostream_check(...);
	public:
		static constexpr auto value = decltype(ostream_check<T>(nullptr))::value;
	};
	/**
	* @brief can_ostream���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto can_ostream_v = saki::can_ostream<T>::value;
}
#endif //SAKI_TYPE_TRAITS_CAN_OSTREAM_2019_01_22