#pragma once
#include <string>

class StringHelper
{
public:
	static std::wstring StringToWide(std::string str);
	static std::string GetDirectoryFromPath(const std::string& filePath);
	static std::string GetFileExtention(const std::string& fileName);
};

