#include "bmp.h"

//Bmpファイルの読み込み
bool BmpApp(const char* path)
{
	ConsoleComment("Bmp");
	//ファイルの読み込み
	std::ifstream ifs(path, std::ios_base::binary);
	if (ifs.fail())
	{
		ConsoleComment(path, "のパスにファイルはありません");
		return false;
	}
	//ヘッダ情報
	char binary[BMP_HEADER_SIZE];
	ifs.read(reinterpret_cast<char*>(&binary), sizeof(binary));
	
	//Bmpファイルかチェック
	if (!BmpCheck(binary))return false;

	//画像の幅と高さ
	unsigned int width, height;
	memcpy(&width, binary + 18, sizeof(width));
	memcpy(&height, binary + 22, sizeof(height));
	ConsoleComment("幅:", width, "px");
	ConsoleComment("高さ:", height, "px");

	//読み込んだ色情報
	std::vector<Color3> color;
	OutputType color4(height, std::vector<Color4>(width));
	std::size_t real_width = width * 3 + width % 4;
	color.resize(real_width);
	//色の読み込み
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
	//ファイルタイプはBM
	std::cout << "ファイルタイプ:" << bmp_header[0] << bmp_header[1] << "->";
	if (bmp_header[0] != 'B' || bmp_header[1] != 'M')
	{
		ConsoleComment("NG");
		ConsoleComment("ファイルタイプがBMではありません");
		return false;
	}
	ConsoleComment("OK");
	//カラービットは24bit
	std::cout << "カラービット:" << unsigned(bmp_header[28]) << "->";
	if (bmp_header[28] != 24)
	{
		ConsoleComment("NG");
		ConsoleComment("カラービットが24bitではありません");
		return false;
	}
	ConsoleComment("OK");
	return true;
}