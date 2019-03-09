#pragma once
#include "../common/common.h"

//BMPファイルのファイルヘッダサイズ
static constexpr std::size_t BMP_FILE_HEADER_SIZE = 14;
//BMPファイルの情報ヘッダサイズ
static constexpr std::size_t BMP_INFO_HEADER_SIZE = 40;
//BMPファイルのヘッダサイズ
static constexpr std::size_t BMP_HEADER_SIZE = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE;

bool BmpApp(const char*);
bool BmpCheck(char[BMP_HEADER_SIZE]);

