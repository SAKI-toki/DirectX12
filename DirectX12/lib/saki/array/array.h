/**
* @file array.h
* @brief �R���p�C�����Œ蒷�z��N���X
* @author �ΎR �I
* @date 2019/01/15
*/
#pragma once
#ifndef SAKI_ARRAY_ARRAY_2019_01_15
#define SAKI_ARRAY_ARRAY_2019_01_15
#include <cstddef>
#include <saki/macro/type_macro.h>
#include <saki/array/details/array_operator.h>

#include <saki/iterator/iterator.h>
#include <saki/iterator/reverse/reverse_iterator.h>

namespace saki
{
	/**
	* @brief �R���p�C�����Œ蒷�z��N���X
	*/
	template<typename T, size_t Size>
	class array
	{
	public:
		SAKI_TYPE_MACRO(T)
	private:
		value_type arr[Size]{};
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		* @details �S��0�ŏ�����
		*/
		constexpr array()
		{}
		/**
		* @brief �z��̗v�f�����l���󂯎��R���X�g���N�^
		* @param u �z��̏������l
		*/
		template<typename ...U>
		explicit constexpr array(const U& ...u) :
			arr{ u... }
		{}
		//�f�t�H���g���g�p
		//�f�t�H���g�ł̓����o�ϐ��̃R�s�[�A���[�u���s��
		array(const array<T, Size>&) = default;
		array<T, Size>& operator=(const array<T, Size>&) = default;
		array(array<T, Size>&&)noexcept = default;
		array<T, Size>& operator=(array<T, Size>&&)noexcept = default;
		/**
		* @brief []���Z�q
		*/
		constexpr reference operator[](size_t index)
		{
			return arr[index];
		}
		/**
		* @brief []���Z�q(constexpr)
		*/
		constexpr const_reference operator[](size_t index)const
		{
			return arr[index];
		}
		/**
		* @brief �z��̑傫�����擾
		* @return �z��̑傫��
		*/
		constexpr size_type size()const
		{
			return Size;
		}

		//�C�e���[�^�[
		constexpr saki::iterator<T> begin()
		{
			return saki::iterator<T>(arr);
		}
		constexpr saki::iterator<T> end()
		{
			return saki::iterator<T>(arr + Size);
		}
		constexpr saki::const_iterator<T> begin()const
		{
			return saki::const_iterator<T>(arr);
		}
		constexpr saki::const_iterator<T> end()const
		{
			return saki::const_iterator<T>(arr + Size);
		}

		constexpr saki::const_iterator<T> cbegin()const
		{
			return this->begin();
		}
		constexpr saki::const_iterator<T> cend()const
		{
			return this->end();
		}
		//���o�[�X�C�e���[�^�[
		constexpr saki::reverse_iterator<saki::iterator<T>> rbegin()
		{
			return saki::reverse_iterator<saki::iterator<T>>(saki::iterator<T>(arr + Size - 1));
		}
		constexpr saki::reverse_iterator<saki::iterator<T>> rend()
		{
			return saki::reverse_iterator<saki::iterator<T>>(saki::iterator<T>(arr - 1));
		}
		constexpr saki::reverse_iterator<saki::const_iterator<T>> rbegin()const
		{
			return saki::reverse_iterator<saki::const_iterator<T>>(saki::const_iterator<T>(arr + Size - 1));
		}
		constexpr saki::reverse_iterator<saki::const_iterator<T>> rend()const
		{
			return saki::reverse_iterator<saki::const_iterator<T>>(saki::const_iterator<T>(arr - 1));
		}

		constexpr saki::reverse_iterator<saki::const_iterator<T>> crbegin()const
		{
			return this->rbegin();
		}
		constexpr saki::reverse_iterator<saki::const_iterator<T>> crend()const
		{
			return this->rend();
		}
	};

	template<typename T>
	class array<T, 0>
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		*/
		constexpr array()
		{}
	};
}
#endif //SAKI_ARRAY_ARRAY_2019_01_15