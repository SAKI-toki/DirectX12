/**
* @file type_macro.h
* @brief value_type,pointer,reference“™‚ğ©“®’è‹`
* @author ÎR —I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_MACRO_TYPE_MACRO_2018_12_13
#define SAKI_MACRO_TYPE_MACRO_2018_12_13
#include <cstddef>

#ifndef SAKI_TYPE_MACRO
#define SAKI_TYPE_MACRO(T)				\
using value_type = T;					\
using size_type = size_t;				\
using difference_type = ptrdiff_t;		\
using pointer = T*;						\
using const_pointer = const T*;			\
using reference = T&;					\
using const_reference = const T&;		\

#endif //SAKI_TYPE_MACRO

#endif //SAKI_MACRO_TYPE_MACRO_2018_12_13