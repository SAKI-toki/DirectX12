/**
* @file fibonacci.h
* @brief �t�B�{�i�b�`������o���֐�
* @author �ΎR �I
* @date 2018/12/28
*/
#pragma once
#ifndef SAKI_MATH_FIBONACCI_2018_12_28
#define SAKI_MATH_FIBONACCI_2018_12_28
#include <cstdint>
#include <cstddef>
#include <saki/math/exchange.h>

namespace saki
{

	/**
	* @brief �t�B�{�i�b�`���񋁂߂�֐�
	* @param N ���߂����ԍ�
	*/
	template<typename T = double>
	constexpr T fibonacci(size_t N)
	{
		T prev1 = 1;
		T prev2 = 1;
		for (size_t i = 3; i <= N; ++i)
		{
			prev2 = saki::exchange(prev1, prev1 + prev2);
		}
		return prev1;
	}

	/**
	* @brief �t�B�{�i�b�`��������߂�֐�
	*/
	template<size_t N, typename T = double>
	constexpr T fibonacci()
	{
		return saki::fibonacci<T>(N);
	}

	/**
	* @brief �^���Ƃ̃t�B�{�i�b�`��
	*/
	template<typename T>
	struct fibonacci_limits
	{
		static constexpr size_t limit = 0;
	};
	template<>
	struct fibonacci_limits<float>
	{
		static constexpr size_t limit = 186;
	};
	template<>
	struct fibonacci_limits<double>
	{
		static constexpr size_t limit = 1476;
	};
	template<>
	struct fibonacci_limits<long double>
	{
		static constexpr size_t limit = 1476;
	};
	template<>
	struct fibonacci_limits<char>
	{
		static constexpr size_t limit = 11;
	};
	template<>
	struct fibonacci_limits<unsigned char>
	{
		static constexpr size_t limit = 13;
	};
	template<>
	struct fibonacci_limits<wchar_t>
	{
		static constexpr size_t limit = 24;
	};
	template<>
	struct fibonacci_limits<char16_t>
	{
		static constexpr size_t limit = 24;
	};
	template<>
	struct fibonacci_limits<char32_t>
	{
		static constexpr size_t limit = 47;
	};
	template<>
	struct fibonacci_limits<short>
	{
		static constexpr size_t limit = 23;
	};
	template<>
	struct fibonacci_limits<unsigned short>
	{
		static constexpr size_t limit = 24;
	};
	template<>
	struct fibonacci_limits<int>
	{
		static constexpr size_t limit = 46;
	};
	template<>
	struct fibonacci_limits<unsigned int>
	{
		static constexpr size_t limit = 47;
	};
	template<>
	struct fibonacci_limits<long>
	{
		static constexpr size_t limit = 46;
	};
	template<>
	struct fibonacci_limits<unsigned long>
	{
		static constexpr size_t limit = 47;
	};
	template<>
	struct fibonacci_limits<long long>
	{
		static constexpr size_t limit = 92;
	};
	template<>
	struct fibonacci_limits<unsigned long long>
	{
		static constexpr size_t limit = 93;
	};
}
#endif //SAKI_MATH_FIBONACCI_2018_12_28