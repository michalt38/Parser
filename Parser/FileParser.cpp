#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "FileParser.h"

namespace
{
	constexpr unsigned prefixSuffixLength = 3u;
}

void FileParser::Parse(const std::string& filePath, const std::string& searchedString)
try
{
	std::ifstream file;
	file.open(filePath);

	if (!file.is_open())
	{
		std::cout << "Cannot open file " << filePath << std::endl;
		return;
	}

	std::string buffer(searchedString.size(), NULL);

	// Calculate position to stop parsing the file
	file.seekg(0, file.end); // Go to the beginning of the file
	const unsigned fileLength = static_cast<unsigned>(file.tellg()); // Get number of characters in a file

	if (searchedString.length() + 1 > fileLength)
		return;

	const unsigned stopPosition = fileLength - static_cast<unsigned>(searchedString.length()) + 1;

	for (unsigned position = 0; position <= stopPosition; ++position)
	{
		// Read string from file with the same length as string we are looking for and starting from next position
		file.seekg(position, file.beg);
		file.read(buffer.data(), searchedString.length());

		if (buffer == searchedString) // Check if this is a string which we are looking for
		{
			std::cout << std::filesystem::path(filePath).filename().string() << "(" << position << "): ";

			// Read prefix
			std::string prefix(prefixSuffixLength, NULL);

			file.seekg(position < prefixSuffixLength ? 0 : position - prefixSuffixLength, file.beg); // Set position to at maximum 3 characters before the match
			file.read(prefix.data(), position < prefixSuffixLength ? position : prefixSuffixLength); // Read as many characters as possible (up to 3)
			file.seekg(position, file.beg); // Restore position

			std::cout << ReplaceSpecialCharactersWithText(prefix) << buffer;

			// Read suffix
			std::string suffix(prefixSuffixLength, NULL);

			file.seekg(position + buffer.size(), file.beg); // Set position to at maximum 3 characters after the match
			file.read(suffix.data(), position + buffer.size() + prefixSuffixLength > fileLength ? fileLength - position - buffer.size() : prefixSuffixLength); // Read as many characters as possible (up to 3)
			file.seekg(position, file.beg); // restore position

			std::cout << ReplaceSpecialCharactersWithText(suffix) << std::endl;
		}
	}

	file.close();
}
catch (...)
{
	throw;
}

std::string FileParser::ReplaceSpecialCharactersWithText(const std::string& str)
{
	std::string result;

	for (unsigned position = 0; position < str.size(); ++position)
	{
		if (str[position] == '\n')
			result += "\\n";
		else if (str[position] == '\t')
			result += "\\t";
		else
			result += str[position];
	}

	return result;
}
