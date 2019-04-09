/**
* @file png.h
* @brief Pngをコンバートする関数の宣言
* @author 石山　悠
* @date 2019/03/15
*/
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <libpng/png.h>
#ifdef _DEBUG
#pragma comment(lib,"debug/libpng16.lib")
#pragma comment(lib,"debug/zlib.lib")
#else
#pragma comment(lib,"release/libpng16.lib")
#pragma comment(lib,"release/zlib.lib")
#endif

static constexpr std::size_t PNG_SIG_SIZE = 8;
struct Color
{
	unsigned char r, g, b, a;
};
using OutputType = std::vector<std::vector<Color>>;

bool ConvertPng(const std::string& path);
bool OutputFile(const std::string path, OutputType& color, int width, int height);