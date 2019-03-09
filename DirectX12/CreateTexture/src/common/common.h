/**
* @file common.h
* @brief 汎用的なデータ
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <saki/type_traits.h>
//RGB
struct Color3
{
	unsigned char r, g, b;
};
//RGB+ALPHA
struct Color4
{
	unsigned char r, g, b, a;
};

//output method
template<typename ...Args,
	typename saki::enable_if_nullptr_t<std::conjunction_v<saki::can_ostream<Args>...>> = nullptr>
	void ConsoleComment(const Args& ...args)
{
	(std::cout << ... << args) << std::endl;
}
using OutputType = std::vector<std::vector<Color4>>;
//パスの最大サイズ
static constexpr std::size_t PATH_SIZE = 256;

/**
* @brief 取得したRGB+ALPHAをファイルに出力する
*/
static void OutputFile(OutputType& color, int width, int height)
{
	//出力するパス
	char o_path[PATH_SIZE];
	ConsoleComment("出力するパスを入力してください");
	std::cin >> o_path;
	std::ofstream ofs(o_path, std::ios_base::binary);
	//幅と高さの書き込み
	ofs.write(reinterpret_cast<char*>(&width), sizeof(width));
	ofs.write(reinterpret_cast<char*>(&height), sizeof(height));

	uint16_t percent = 0;
	//書き込み
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			ofs.write(reinterpret_cast<char*>(&color[i][j].r), sizeof(unsigned char));
			ofs.write(reinterpret_cast<char*>(&color[i][j].g), sizeof(unsigned char));
			ofs.write(reinterpret_cast<char*>(&color[i][j].b), sizeof(unsigned char));
			ofs.write(reinterpret_cast<char*>(&color[i][j].a), sizeof(unsigned char));
		}
		const uint16_t new_percent = static_cast<uint16_t>((i + 1.0f) / height * 100);
		if (percent != new_percent)
		{
			percent = new_percent;
			std::cout << "\r" << percent << "%";
		}
	}
	ConsoleComment();
	ConsoleComment("変換成功");
	ofs.close();
}
