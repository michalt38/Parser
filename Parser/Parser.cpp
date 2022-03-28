/**
*	Program for searching directories and text files for a given input string occurances
*	First parameter is a path to directory or text file and the second one is a string to search for (up to 128 characters)
*/

#include <iostream>
#include <string>
#include <filesystem>

#include "FileParser.h"
#include "DirParser.h"

namespace
{
	constexpr unsigned searchedStringMaxLength = 128u;
}

int main(int argc, char** argv)
try
{
	if (argc < 3)
	{
		std::cout << "Unproper number of input parameters" << std::endl;
		return 0x01;
	}

	std::string path = std::string(argv[1]);
	std::string searchedString;

	for (int i = 2; i < argc; ++i)
	{
		if (!searchedString.empty())
			searchedString += " ";

		searchedString += std::string(argv[i]);

		if (searchedString.size() > searchedStringMaxLength)
		{
			searchedString.resize(searchedStringMaxLength);
			break;
		}
	}

	DirParser::Parse(path, searchedString);

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
	return 0x01;
}
catch (...)
{
	std::cout << "Unexpected error occured" << std::endl;
	return 0x01;
}