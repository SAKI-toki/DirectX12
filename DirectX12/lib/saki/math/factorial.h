/**
* @file factorial.h
* @brief �K��
* @author �ΎR �I
* @date 2019/01/06
*/
#pragma once
#ifndef SAKI_MATH_FACTORIAL_2019_01_06
#define SAKI_MATH_FACTORIAL_2019_01_06
#include <cstdint>
#include <cstddef>

namespace saki
{
	/**
	* @brief �K��(�����o�[�W����)
	* @param N 1����N�܂ł̊K������߂�
	*/
	template<typename T = double>
	constexpr T factorial(size_t N)
	{
		T sum = 1;
		for (size_t i = 2; i <= N; ++i)
		{
			sum *= static_cast<T>(i);
		}
		return sum;
	}
	/**
	* @brief �K��(�������o�[�W����)
	*/
	template<size_t N, typename T = double>
	constexpr T factorial()
	{
		return factorial<T>(N);
	}


	/**
	* @brief �^���Ƃ̍ő�K�搔
	*/
	template<typename T>
	struct factorial_limits
	{
		static constexpr size_t limit = 0;
	};
	template<>
	struct factorial_limits<float>
	{
		static constexpr size_t limit = 34;
	};
	template<>
	struct factorial_limits<double>
	{
		static constexpr size_t limit = 170;
	};
	template<>
	struct factorial_limits<long double>
	{
		static constexpr size_t limit = 170;
	};
	template<>
	struct factorial_limits<char>
	{
		static constexpr size_t limit = 5;
	};
	template<>
	struct factorial_limits<unsigned char>
	{
		static constexpr size_t limit = 6;
	};
	template<>
	struct factorial_limits<wchar_t>
	{
		static constexpr size_t limit = 8;
	};
	template<>
	struct factorial_limits<char16_t>
	{
		static constexpr size_t limit = 8;
	};
	template<>
	struct factorial_limits<char32_t>
	{
		static constexpr size_t limit = 13;
	};
	template<>
	struct factorial_limits<short>
	{
		static constexpr size_t limit = 7;
	};
	template<>
	struct factorial_limits<unsigned short>
	{
		static constexpr size_t limit = 8;
	};
	template<>
	struct factorial_limits<int>
	{
		static constexpr size_t limit = 13;
	};
	template<>
	struct factorial_limits<unsigned int>
	{
		static constexpr size_t limit = 13;
	};
	template<>
	struct factorial_limits<long>
	{
		static constexpr size_t limit = 13;
	};
	template<>
	struct factorial_limits<unsigned long>
	{
		static constexpr size_t limit = 13;
	};
	template<>
	struct factorial_limits<long long>
	{
		static constexpr size_t limit = 20;
	};
	template<>
	struct factorial_limits<unsigned long long>
	{
		static constexpr size_t limit = 22;
	};
}
#endif //SAKI_MATH_FACTORIAL_2019_01_06