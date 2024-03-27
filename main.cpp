#include <iostream>
#include <fstream>
#include <exception>
#include "include/parser.h"

using namespace d_parser;
int main() {
	try
	{
		std::string fileName = "/home/mike/work/COMPILER-FLINT/JAVA-DRAGON-COMP/java-dragon-comp/TEST/resources/tests/block1.t";
		std::ifstream in(fileName);
		std::vector<char> text((std::istreambuf_iterator<char>(in)),
		                           std::istreambuf_iterator<char>());
		in.close();

		Parser p(text);
		p.program();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}
