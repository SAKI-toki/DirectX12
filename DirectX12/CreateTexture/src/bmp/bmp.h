#pragma once
#include "../common/common.h"

//BMP�t�@�C���̃t�@�C���w�b�_�T�C�Y
static constexpr std::size_t BMP_FILE_HEADER_SIZE = 14;
//BMP�t�@�C���̏��w�b�_�T�C�Y
static constexpr std::size_t BMP_INFO_HEADER_SIZE = 40;
//BMP�t�@�C���̃w�b�_�T�C�Y
static constexpr std::size_t BMP_HEADER_SIZE = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

bool BmpApp(const char*);
bool BmpCheck(char[BMP_HEADER_SIZE]);

