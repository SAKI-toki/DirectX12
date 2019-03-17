#include "png/png.h"


int main()
{
	std::cout << "path‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢" << std::endl;
	std::string path;
	std::cin >> path;
	return ConvertPng(path) ? 0 : -1;
}