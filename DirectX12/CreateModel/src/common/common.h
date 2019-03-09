/**
* @file common.h
* @brief �ėp�I�ȃf�[�^
* @author �ΎR�@�I
* @date 2019/02/17
*/
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <saki/type_traits.h>
#include <string>
#include <saki/vector.h>

//output method
template<typename ...Args,
	typename saki::enable_if_nullptr_t<std::conjunction_v<saki::can_ostream<Args>...>> = nullptr>
	void ConsoleComment(const Args& ...args)
{
	(std::cout << ... << args) << std::endl;
}
//�p�X�̍ő�T�C�Y
static constexpr std::size_t PATH_SIZE = 256;