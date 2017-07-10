#pragma once
#include <string>
#include <vector>

class Tool
{
public:
	Tool();
	~Tool();

	//字符串分割函数
	static void splitString(const std::string &input, std::vector<std::string> &output, std::string &delim);
	//文件路径格式转换（\转成\\):Windows
	static bool filePathConvert(std::string &filePath);
};

