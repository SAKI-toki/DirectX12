/**
* @file common.h
* @brief �ėp�I�ȃf�[�^
* @author �ΎR�@�I
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
//�p�X�̍ő�T�C�Y
static constexpr std::size_t PATH_SIZE = 256;

/**
* @brief �擾����RGB+ALPHA���t�@�C���ɏo�͂���
*/
static void OutputFile(OutputType& color, int width, int height)
{
	//�o�͂���p�X
	char o_path[PATH_SIZE];
	ConsoleComment("�o�͂���p�X����͂��Ă�������");
	std::cin >> o_path;
	std::ofstream ofs(o_path, std::ios_base::binary);
	//���ƍ����̏�������
	ofs.write(reinterpret_cast<char*>(&width), sizeof(width));
	ofs.write(reinterpret_cast<char*>(&height), sizeof(height));

	uint16_t percent = 0;
	//��������
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
	ConsoleComment("�ϊ�����");
	ofs.close();
}
