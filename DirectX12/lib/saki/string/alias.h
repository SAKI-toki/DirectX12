/**
* @file alias.h
* @brief string_baseを使用しやすく、エイリアス宣言しておく
* @author 石山 悠
* @date 2019/01/22
*/
#pragma once
#ifndef SAKI_STRING_ALIAS_2019_01_22
#define SAKI_STRING_ALIAS_2019_01_22
#include <saki/string/base/string_base.h>

namespace saki
{
	template<size_t N>
	using string = saki::string_base<char, N>;
}
#endif //SAKI_STRING_ALIAS_2019_01_22
