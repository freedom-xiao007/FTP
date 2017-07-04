#pragma once
#include <string>
#include <vector>

class Tool
{
public:
	Tool();
	~Tool();

	//×Ö·û´®·Ö¸îº¯Êý
	static void splitString(const std::string &input, std::vector<std::string> &output, std::string &delim);
};

