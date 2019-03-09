/**
* @file reverse_iterator.h
* @brief 逆方向に進むイテレーター
* @author 石山 悠
* @date 2019/01/13
*/
#pragma once
#ifndef SAKI_ITERATOR_REVERSE_REVERSE_ITERATOR_2019_01_13
#define SAKI_ITERATOR_REVERSE_REVERSE_ITERATOR_2019_01_13
#include <saki/iterator/reverse/details/reverse_iterator_base.h>

namespace saki
{
	/**
	* @brief ノーマルなリバースイテレーター
	*/
	template<typename T>
	class reverse_iterator :public saki::details::reverse_iterator_base<T>
	{
	public:
		explicit constexpr reverse_iterator(T pointer) :saki::details::reverse_iterator_base<T>(pointer) {}
	};
	/**
	* @brief constなリバースイテレーター
	*/
	template<typename T>
	class const_reverse_iterator :public saki::details::reverse_iterator_base<const T>
	{
	public:
		explicit constexpr const_reverse_iterator(const T pointer) :saki::details::reverse_iterator_base<const T>(pointer) {}
	};
}
#endif //SAKI_ITERATOR_REVERSE_REVERSE_ITERATOR_2019_01_13