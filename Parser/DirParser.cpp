#include <filesystem>
#include <iostream>

#include "DirParser.h"
#include "FileParser.h"

void DirParser::Parse(const std::string& path, const std::string& searchedString)
try
{
	if (IsTextFile(std::filesystem::directory_entry(path)))
	{
		FileParser::Parse(path, searchedString);
		return;
	}

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (IsTextFile(entry))
		{
			FileParser::Parse(entry.path().string(), searchedString);
		}
		else if (entry.is_directory())
		{
			Parse(entry.path().string(), searchedString);
		}
	}
}
catch (...)
{
	throw;
}

bool DirParser::IsTextFile(const std::filesystem::directory_entry& entry)
{
	return entry.is_regular_file() && entry.path().extension() == ".txt";
}
