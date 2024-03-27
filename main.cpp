#include <iostream>
#include <fstream>
#include <exception>
#include "include/parser.h"

using namespace d_parser;
int main(int argc, char *argv[]) {
	try
	{
		std::string fileName;
		bool done= false;
		for(;!done;){
			int c;
			switch (c=getopt(argc, argv, "hvf:")) {
				case 'h':
					std::cout << "Usage: " << argv[0] << " -h -v -f <file>" << std::endl;
					exit(0);
				case 'v':
					std::cout << "Version 1.0" << std::endl;
					exit(0);
				case 'f':
					std::cout << "File: " << optarg << std::endl;
					fileName = optarg;
					done= true;
					break;
				case '?':
					std::cout << "Unknown option: " << optopt << std::endl;
					exit(0);
				case -1:
				default:
					std::cout << "getopt() returned character code 0%o" << c << std::endl;
					exit(0);
			}
		}
		

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
