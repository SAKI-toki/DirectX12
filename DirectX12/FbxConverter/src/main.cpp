#include "fbx/fbx.h"

int main()
{
	std::string path;
	std::cout << "�R���o�[�g����fbx�̃p�X����͂��Ă�������" << std::endl;
	std::cin >> path;
	bool app = ConvertFbx(path);
	system("pause");
	return app ? 0 : -1;
}