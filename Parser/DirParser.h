#pragma once
#include <string>

/** Class DirParser
*	Scans the directories recursively and runs parsing the text files in separate threads.
*/
class DirParser
{
public:
	DirParser() = delete;

	static void Parse(const std::string& filePath, const std::string& searchedString);

private:
	static bool IsTextFile(const std::filesystem::directory_entry& entry);
};

