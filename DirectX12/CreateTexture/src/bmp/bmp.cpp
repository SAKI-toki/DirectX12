#include "bmp.h"

//Bmp�t�@�C���̓ǂݍ���
bool BmpApp(const char* path)
{
	ConsoleComment("Bmp");
	//�t�@�C���̓ǂݍ���
	std::ifstream ifs(path, std::ios_base::binary);
	if (ifs.fail())
	{
		ConsoleComment(path, "�̃p�X�Ƀt�@�C���͂���܂���");
		return false;
	}
	//�w�b�_���
	char binary[BMP_HEADER_SIZE];
	ifs.read(reinterpret_cast<char*>(&binary), sizeof(binary));
	
	//Bmp�t�@�C�����`�F�b�N
	if (!BmpCheck(binary))return false;

	//�摜�̕��ƍ���
	unsigned int width, height;
	memcpy(&width, binary + 18, sizeof(width));
	memcpy(&height, binary + 22, sizeof(height));
	ConsoleComment("��:", width, "px");
	ConsoleComment("����:", height, "px");

	//�ǂݍ��񂾐F���
	std::vector<Color3> color;
	OutputType color4(height, std::vector<Color4>(width));
	std::size_t real_width = width * 3 + width % 4;
	color.resize(real_width);
	//�F�̓ǂݍ���
	for (unsigned int i = 0; i < height; ++i)
	{
		ifs.read(reinterpret_cast<char*>(&color[0]), color.size());
		for (unsigned int j = 0; j < width; ++j)
		{
			color4[height - 1 - i][j].r = color[j].r;
			color4[height - 1 - i][j].g = color[j].g;
			color4[height - 1 - i][j].b = color[j].b;
			color4[height - 1 - i][j].a = 0xff;
		}
	}

	OutputFile(color4, width, height);
	ifs.close();
	return true;
}

bool BmpCheck(char bmp_header[BMP_HEADER_SIZE])
{
	//�t�@�C���^�C�v��BM
	std::cout << "�t�@�C���^�C�v:" << bmp_header[0] << bmp_header[1] << "->";
	if (bmp_header[0] != 'B' || bmp_header[1] != 'M')
	{
		ConsoleComment("NG");
		ConsoleComment("�t�@�C���^�C�v��BM�ł͂���܂���");
		return false;
	}
	ConsoleComment("OK");
	//�J���[�r�b�g��24bit
	std::cout << "�J���[�r�b�g:" << unsigned(bmp_header[28]) << "->";
	if (bmp_header[28] != 24)
	{
		ConsoleComment("NG");
		ConsoleComment("�J���[�r�b�g��24bit�ł͂���܂���");
		return false;
	}
	ConsoleComment("OK");
	return true;
}