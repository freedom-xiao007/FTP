#pragma once
#include <string>
#include <vector>

class Tool
{
public:
	Tool();
	~Tool();

	//�ַ����ָ��
	static void splitString(const std::string &input, std::vector<std::string> &output, std::string &delim);
	//�ļ�·����ʽת����\ת��\\):Windows
	static bool filePathConvert(std::string &filePath);
};

