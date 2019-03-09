/**
* @file int_to_string.h
* @brief intå^Ç©ÇÁstringå^Ç…ïœä∑
* @author êŒéR óI
* @date 2019/01/26
*/
#pragma once
#ifndef SAKI_STRING_TO_STRING_INT_TO_STRING_2019_01_26
#define SAKI_STRING_TO_STRING_INT_TO_STRING_2019_01_26
#include <cstddef>
#include <limits>
#include <type_traits>
#include <saki/math/details/pow_n.h>
#include <saki/math/digit_count.h>
#include <saki/math/abs.h>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/string/base/string_base.h>

namespace saki
{
	/**
	* @brief intå^Ç©ÇÁstringå^Ç…ïœä∑
	* @details å≈íËí∑ÇÃÇΩÇﬂÉTÉCÉYéwíËÇµÇ»ÇØÇÍÇŒÇ»ÇÁÇ»Ç¢
	*/
	template<typename T, typename Integer,
		size_t N = saki::digit_count(std::numeric_limits<Integer>::max()) + 1, 
		typename StringType = saki::string_base<T, N>,
		typename saki::enable_if_nullptr_t<std::is_integral_v<Integer>> = nullptr>
		constexpr StringType int_to_string(Integer x)
	{
		if (x == 0)
		{
			return StringType{ "0" };
		}
		StringType str;
		size_t index = 0;
		if (x < 0)
		{
			str[index++] = '-';
			x = saki::abs(x);
		}
		size_t digit = saki::digit_count(x);
		for (size_t i = digit; i > 0; --i)
		{
			auto pow10 = saki::details::pow_n(10, i - 1);
			auto digit_n = x / pow10;
			str[index++] = static_cast<T>('0' + digit_n);
			x -= digit_n * pow10;
		}
		return str;
	}

}

#endif //SAKI_STRING_TO_STRING_INT_TO_STRING_2019_01_26