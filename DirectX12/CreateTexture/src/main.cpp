#define _CRT_SECURE_NO_WARNINGS
#include "common/common.h"
#include "bmp/bmp.h"
#include "png/png.h"

//�G���g���[
int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		//char path[PATH_SIZE];
		//ConsoleComment("�R���o�[�g����t�@�C���p�X����͂��Ă�������");
		//std::cin >> path;
		ConsoleComment(argv[i], "���R���o�[�g���܂�");
		if (PngApp(argv[i]))
		{
			ConsoleComment("Png����R���o�[�g����");
		}
		else if (BmpApp(argv[i]))
		{
			ConsoleComment("Bmp����R���o�[�g����");
		}
		else
		{
			ConsoleComment("���̃t�@�C���͑Ή����Ă��܂���");
		}
	}
	ConsoleComment("�I��");
	return 0;
}


