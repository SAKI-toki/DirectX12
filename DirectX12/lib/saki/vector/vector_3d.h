/**
* @file vector_3d.h
* @brief 3�����ł̃x�N�g��
* @author �ΎR �I
* @date 2018/12/06
*/
#pragma once
#ifndef SAKI_VECTOR_VECTOR_3D_2018_12_06
#define SAKI_VECTOR_VECTOR_3D_2018_12_06
#include <limits> //for numeric_limits
#include <saki/math/sqrt.h> //for constexpr_sqrt
#include <saki/vector/details/3d/vector_3d_operator.h>
#include <saki/macro/type_macro.h>
#include <cmath>

namespace saki
{
	/**
	* @brief 3�����ł̃x�N�g��
	*/
	template<typename T>
	class vector3
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		value_type 
			x = static_cast<value_type>(0),
			y = static_cast<value_type>(0), 
			z = static_cast<value_type>(0);
		/**
		* @brief �����Ȃ��R���X�g���N�^
		* @details �S��0�ŏ�����
		*/
		constexpr vector3()
		{}
		/**
		* @brief ��������R���X�g���N�^
		* @param _x x�̏����l
		* @param _y y�̏����l
		* @param _z z�̏����l
		*/
		constexpr vector3(const_reference _x, const_reference _y, const_reference _z) :
			x(_x), y(_y), z(_z)
		{}
		//�f�t�H���g���g�p
		//�f�t�H���g�ł̓����o�ϐ��̃R�s�[�A���[�u���s��
		vector3(const vector3<value_type>&) = default;
		vector3<value_type>& operator=(const vector3<value_type>&) = default;
		vector3(vector3<value_type>&&)noexcept = default;
		vector3<value_type>& operator=(vector3<value_type>&&)noexcept = default;
		/**
		* @brief +=���Z�q
		*/
		template<typename U = value_type>
		constexpr auto operator+=(const saki::vector3<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=���Z�q
		*/
		template<typename U = value_type>
		constexpr auto operator-=(const saki::vector3<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=���Z�q(�X�J��)
		*/
		template<typename U = value_type>
		constexpr auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief *=���Z�q(�x�N�g��)
		*/
		template<typename U = value_type>
		constexpr auto operator*=(const saki::vector3<U>& other)
		{
			*this = *this * other;
			return *this;
		}
		/**
		* @brief /=���Z�q(�X�J��)
		*/
		template<typename U = value_type>
		constexpr auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief /=���Z�q(�x�N�g��)
		*/
		template<typename U = value_type>
		constexpr auto operator/=(const saki::vector3<U>& other)
		{
			*this = *this / other;
			return *this;
		}
		/**
		* @brief �P��+���Z�q
		*/
		constexpr saki::vector3<value_type> operator+()const
		{
			return *this;
		}
		/**
		* @brief �P��-���Z�q
		*/
		constexpr saki::vector3<value_type> operator-()const
		{
			return saki::vector3<value_type>(this->x * (-1), this->y * (-1), this->z * (-1));
		}
		/**
		* @brief []���Z�q
		*/
		constexpr reference operator[](const size_type index)
		{
			return (index == 0) ? this->x : (index == 1) ? this->y : this->z;
		}
		/**
		* @brief []���Z�q(constexpr)
		*/
		constexpr const_reference operator[](const size_type index)const
		{
			return (index == 0) ? this->x : (index == 1) ? this->y : this->z;
		}
		/**
		* @brief ++���Z�q(�O�u)
		*/
		constexpr saki::vector3<value_type>& operator++()
		{
			this->x += 1; this->y += 1; this->z += 1;
			return *this;
		}
		/**
		* @brief ++���Z�q(��u)
		*/
		constexpr saki::vector3<value_type> operator++(int)
		{
			saki::vector3<value_type> temp = *this;
			this->x += 1; this->y += 1; this->z += 1;
			return temp;
		}
		/**
		* @brief --���Z�q(�O�u)
		*/
		constexpr saki::vector3<value_type>& operator--()
		{
			this->x -= 1; this->y -= 1; this->z -= 1;
			return *this;
		}
		/**
		* @brief --���Z�q(��u)
		*/
		constexpr saki::vector3<value_type> operator--(int)
		{
			saki::vector3<value_type> temp = *this;
			this->x -= 1; this->y -= 1; this->z -= 1;
			return temp;
		}
		/**
		* @brief ���K��
		* @details int�^�̏ꍇ�A���ׂĂ̗v�f��0�ŕԂ�܂�
		*/
		constexpr void normalize()
		{
			//����
			auto den = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
			if (den == 0)
			{
				this->x = 0;
				this->y = 0;
				this->z = 0;
			}
			else
			{
				this->x /= den;
				this->y /= den;
				this->z /= den;
			}
		}

	};

	/**
	* @brief vector3�̃I�[���[��
	*/
	template<typename T>
	static constexpr saki::vector3<T> vector3_zero{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
	/**
	* @brief vector3�̃I�[������
	*/
	template<typename T>
	static constexpr saki::vector3<T> vector3_one{ static_cast<T>(1), static_cast<T>(1), static_cast<T>(1) };
	/**
	* @brief vector3�̍ŏ��l
	*/
	template<typename T>
	static constexpr saki::vector3<T> vector3_min{ std::numeric_limits<T>::min(), std::numeric_limits<T>::min(), std::numeric_limits<T>::min() };
	/**
	* @brief vector3�̍ő�l
	*/
	template<typename T>
	static constexpr saki::vector3<T> vector3_max{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };
	/**
	* @brief ���K��
	* @return ���K����������
	*/
	template<typename U = double, typename T>
	constexpr saki::vector3<U> normalize(const saki::vector3<T>& v)
	{
		//����
		auto den = saki::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (den == 0)
		{
			return saki::vector3<U>
				(static_cast<U>(0),//x
					static_cast<U>(0),//y
					static_cast<U>(0));//z
		}
		else
		{
			return saki::vector3<U>
				(static_cast<U>(v.x / den),//x
					static_cast<U>(v.y / den),//y
					static_cast<U>(v.z / den));//z
		}
	}
	/**
	* @brief ����
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U dot(const saki::vector3<T1>& v1, const saki::vector3<T2>& v2)
	{
		return static_cast<U>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
	/**
	* @brief �O��
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr saki::vector3<U> cross(const saki::vector3<T1>& v1, const saki::vector3<T2>& v2)
	{
		return saki::vector3<U>(
			v1.y * v2.z - v1.z * v1.y, //x
			v1.z * v2.x - v1.x * v1.z, //y
			v1.x * v2.y - v1.y * v1.x);//z
	}
	/**
	* @brief ���`���
	* @details Quaternion�͎g�p���Ă��܂���
	*/
	template<typename U = double, typename T1, typename T2, typename T = double>
	constexpr saki::vector3<U> lerp(const saki::vector3<T1>& v1, const saki::vector3<T2>& v2, const T& t, const T& base = 1)
	{
		auto ratio = t / base;
		return saki::vector3<U>(
			v1.x + (v2.x - v1.x) * ratio,
			v1.y + (v2.y - v1.y) * ratio,
			v1.z + (v2.z - v1.z) * ratio);
	}
}

#endif //SAKI_VECTOR_VECTOR_3D_2018_12_06