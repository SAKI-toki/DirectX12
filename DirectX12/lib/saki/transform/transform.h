/**
* @file transform.h
* @brief transform�N���X
* @author �ΎR �I
* @date 2018/12/18
*/
#pragma once
#ifndef SAKI_TRANSFORM_TRANSFORM_2018_12_18
#define SAKI_TRANSFORM_TRANSFORM_2018_12_18
#include <saki/vector/vector_3d.h>
#include <saki/transform/details/transform_operator.h>

namespace saki
{
	/**
	* @brief transform�N���X
	* @details �N�H�[�^�j�I���͎g�p���Ă��܂���
	*/
	template<typename T>
	class transform
	{
		//�ʒu
		saki::vector3<T> position;
		//��]
		saki::vector3<T> rotation;
		//�g�k
		saki::vector3<T> scale = saki::vector3<T>{ static_cast<T>(1),static_cast<T>(1),static_cast<T>(1) };
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		*/
		constexpr transform()
		{}
		/**
		* @brief �e�l�������ɂƂ�R���X�g���N�^
		* @param pos �ʒu
		* @param rot ��]
		* @param sca �g�k
		*/
		constexpr transform(const saki::vector3<T>& pos, const saki::vector3<T> rot, const saki::vector3<T>sca) :
			position(pos), rotation(rot), scale(sca)
		{}
		//�R�s�[���[�u�̓f�t�H���g���g�p
		transform(const transform<T>&) = default;
		transform<T>& operator=(const transform<T>&) = default;
		transform(transform<T>&&) = default;
		transform<T>& operator=(transform<T>&&) = default;

		/**
		* @brief �ړ�
		* @param pos �ړ���
		*/
		constexpr void move(const saki::vector3<T>& pos)
		{
			position += pos;
		}
		/**
		* @brief �ړ�
		* @param x �ړ���(x)
		* @param y �ړ���(y)
		* @param z �ړ���(z)
		*/
		constexpr void move(const T& x, const T& y, const T& z)
		{
			position += saki::vector3<T>(x, y, z);
		}
		/**
		* @brief ��]
		* @param rot ��]��
		*/
		constexpr void rotate(const saki::vector3<T>& rot)
		{
			rotation += rot;
		}
		/**
		* @brief ��]
		* @param x ��]��(x)
		* @param y ��]��(y)
		* @param z ��]��(z)
		*/
		constexpr void rotate(const T& x, const T& y, const T& z)
		{
			rotation += saki::vector3<T>(x, y, z);
		}
		/**
		* @brief �g��
		* @param sca �g���
		*/
		constexpr void expantion(const saki::vector3<T>& sca)
		{
			scale += sca;
		}
		/**
		* @brief �g��
		* @param x �g���(x)
		* @param y �g���(y)
		* @param z �g���(z)
		*/
		constexpr void expantion(const T& x, const T& y, const T& z)
		{
			scale += saki::vector3<T>(x, y, z);
		}
		/**
		* @brief �ʒu�̃Q�b�^
		* @return �ʒu
		*/
		constexpr auto get_pos()const
		{
			return position;
		}
		/**
		* @brief �ʒu�̃Z�b�^
		* @param pos �ʒu
		*/
		constexpr void set_pos(const saki::vector3<T>& pos)
		{
			position = pos;
		}
		/**
		* @brief ��]�̃Q�b�^
		* @return ��]
		*/
		constexpr auto get_rot()const
		{
			return rotation;
		}
		/**
		* @brief ��]�̃Z�b�^
		* @param rot ��]
		*/
		constexpr void set_rot(const saki::vector3<T>& rot)
		{
			rotation = rot;
		}
		/**
		* @brief �g�k�̃Q�b�^
		* @return �g�k
		*/
		constexpr auto get_scale()const
		{
			return scale;
		}
		/**
		* @brief �g�k�̃Z�b�^
		* @param sca �g�k
		*/
		constexpr void set_scale(const saki::vector3<T>& sca)
		{
			scale = sca;
		}
		/**
		* @brief +=���Z�q
		*/
		template<typename U = T>
		constexpr auto operator+=(const saki::transform<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=���Z�q
		*/
		template<typename U = T>
		constexpr auto operator-=(const saki::transform<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=���Z�q(�X�J��)
		*/
		template<typename U = T>
		constexpr auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief /= ���Z�q(�X�J��)
		*/
		template<typename U = T>
		constexpr auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief �P��+���Z�q
		*/
		constexpr saki::transform<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief �P��-���Z�q
		*/
		constexpr saki::transform<T> operator-()const
		{
			return saki::transform<T>(this->position * (-1), this->rotation * (-1), this->scale * (-1));
		}
	};
}

#endif //SAKI_TRANSFORM_TRANSFORM_2018_12_18