#include "fbx/fbx.h"

int main()
{
	std::string path;
	std::cout << "コンバートするfbxのパスを入力してください" << std::endl;
	std::cin >> path;
	bool app = ConvertFbx(path);
	system("pause");
	return app ? 0 : -1;
}