#include "fbx/fbx.h"

int main()
{
	std::string path;
	std::cin >> path;
	bool app = ConvertFbx(path);
	system("pause");
	return app ? 0 : -1;
}