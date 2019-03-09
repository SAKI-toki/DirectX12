#include "obj/obj.h"
int main()
{
	char path[PATH_SIZE];
	std::cin >> path;
	ObjApp(path);
	system("pause");
	return 0;
}