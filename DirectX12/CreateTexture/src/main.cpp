#define _CRT_SECURE_NO_WARNINGS
#include "common/common.h"
#include "bmp/bmp.h"
#include "png/png.h"

//エントリー
int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		//char path[PATH_SIZE];
		//ConsoleComment("コンバートするファイルパスを入力してください");
		//std::cin >> path;
		ConsoleComment(argv[i], "をコンバートします");
		if (PngApp(argv[i]))
		{
			ConsoleComment("Pngからコンバート成功");
		}
		else if (BmpApp(argv[i]))
		{
			ConsoleComment("Bmpからコンバート成功");
		}
		else
		{
			ConsoleComment("このファイルは対応していません");
		}
	}
	ConsoleComment("終了");
	return 0;
}


