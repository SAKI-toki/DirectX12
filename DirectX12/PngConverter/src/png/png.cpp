/**
* @file png.cpp
* @brief Png���R���o�[�g����֐��̒�`
* @author �ΎR�@�I
* @date 2019/03/15
*/
#include "png.h"
#include <iostream>
#include <fstream>

/**
* @brief Png�t�@�C���̃R���o�[�g
* @param patht Png�t�@�C���̃p�X
* @return ����ɃR���o�[�g�ł������ǂ���
*/
bool ConvertPng(const std::string& path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path.c_str(), "rb");
	std::cout << "�t�@�C�����I�[�v�� : ";
	if (fp == NULL)
	{
		std::cout << "���s" << std::endl;
		return false;
	}
	std::cout << "����" << std::endl;
	int  x, y;
	int width, height;
	png_structp png = NULL;
	png_infop info = NULL;
	png_bytep row;
	png_bytepp rows;
	png_byte sig_bytes[PNG_SIG_SIZE];
	std::cout << "�t�@�C���̓ǂݍ��� : ";
	//�t�@�C���̓ǂݍ���
	if (fread(sig_bytes, sizeof(sig_bytes), 1, fp) != 1)
	{
		std::cout << "���s" << std::endl;
		return false;
	}
	std::cout << "����" << std::endl;
	std::cout << "Png���ǂ��� : ";
	//PNG���ǂ�������
	if (png_sig_cmp(sig_bytes, 0, sizeof(sig_bytes)))
	{
		std::cout << "Png�ł͂���܂���" << std::endl;
		return false;
	}
	std::cout << "Png�ł�" << std::endl;
	try
	{
		png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (png == NULL)
		{
			throw 0;
		}
		info = png_create_info_struct(png);
		if (info == NULL)
		{
			throw 0;
		}
		if (setjmp(png_jmpbuf(png)))
		{
			throw 0;
		}
		png_init_io(png, fp);
		png_set_sig_bytes(png, sizeof(sig_bytes));
		png_read_png(png, info, PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16, NULL);
		width = png_get_image_width(png, info);
		height = png_get_image_height(png, info);
		rows = png_get_rows(png, info);
		png_byte color_type = png_get_color_type(png, info);
		if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGB_ALPHA)
		{
			std::cout << "�J���[�^�C�v���Ή����Ă��܂���" << std::endl;
			throw 0;
		}
		std::cout << "��:" << width << "px" << std::endl;
		std::cout << "����:" << height << "px" << std::endl;
		OutputType color(height, std::vector<Color>(width));
		std::cout << "�J���[�^�C�v:";
		//�摜�`���ɉ����ċl�ߍ���
		switch (png_get_color_type(png, info))
		{
		case PNG_COLOR_TYPE_RGB:  // RGB
		{
			std::cout << "RGB" << std::endl;
			for (y = 0; y < height; y++)
			{
				row = rows[y];
				for (x = 0; x < width; x++)
				{
					color[y][x].b = *row++;
					color[y][x].g = *row++;
					color[y][x].r = *row++;
					color[y][x].a = 0xff;
				}
			}
		}
		break;
		case PNG_COLOR_TYPE_RGB_ALPHA:  // RGBA
		{
			std::cout << "RGB_ALPHA" << std::endl;
			for (y = 0; y < height; y++)
			{
				row = rows[y];
				for (x = 0; x < width; x++)
				{
					color[y][x].b = *row++;
					color[y][x].g = *row++;
					color[y][x].r = *row++;
					color[y][x].a = *row++;
				}
			}
		}
		break;
		}
		if (!OutputFile(path, color, width, height))throw 0;
	}
	catch (...)
	{
		png_destroy_read_struct(&png, &info, NULL);
		return false;
	}
	png_destroy_read_struct(&png, &info, NULL);
	return true;
}

/**
* @brief �t�@�C���ɏo�͂���
* @param path �p�X
* @param color �F���
* @param width,height �T�C�Y
*/
bool OutputFile(const std::string path, OutputType& color, int width, int height)
{
	std::ofstream ofs(
		path.substr(0, path.size() - 3) + std::string("sakitex"),
		std::ios_base::binary);
	if (ofs.fail())
	{
		std::cout << "����Ƀt�@�C�����J���܂���ł���(�����ł��܂���ł���)" << std::endl;
		return false;
	}
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
	std::cout << std::endl;
	std::cout << "�ϊ�����" << std::endl;
	ofs.close();
	return true;
}