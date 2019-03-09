/**
* @file iterator.h
* @brief �R���p�C����iterator
* @author �ΎR �I
* @date 2019/01/09
*/
#pragma once
#ifndef SAKI_ITERATOR_ITERATOR_2019_01_09
#define SAKI_ITERATOR_ITERATOR_2019_01_09
#include <saki/macro/type_macro.h>
#include <saki/iterator/details/iterator_base.h>


namespace saki
{
	/**
	* @brief �m�[�}���ȃC�e���[�^�[
	*/
	template<typename T>
	class iterator :public saki::details::iterator_base<T>
	{
	public:
		explicit constexpr iterator(T* pointer) :saki::details::iterator_base<T>(pointer) {}
	};
	/**
	* @brief const�ȃC�e���[�^�[
	*/
	template<typename T>
	class const_iterator:public saki::details::iterator_base<const T>
	{
	public:
		explicit constexpr const_iterator(const T* pointer) :saki::details::iterator_base<const T>(pointer) {}
	};
}
#endif //SAKI_ITERATOR_ITERATOR_2019_01_09