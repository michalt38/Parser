#pragma once
#include <string>

/** Class FileParser
*	Scans the text file and looks for a given string=
*/
class FileParser
{
public:
	FileParser() = delete;

	static void Parse(const std::string& filePath, const std::string& searchedString);

private:
	// Used to format tabs as "\t" and new lines as "\n"
	static std::string ReplaceSpecialCharactersWithText(const std::string& str);
};
