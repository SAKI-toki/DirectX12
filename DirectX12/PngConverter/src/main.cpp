#include "png/png.h"


int main()
{
	std::cout << "path����͂��Ă�������" << std::endl;
	std::string path;
	std::cin >> path;
	return ConvertPng(path) ? 0 : -1;
}