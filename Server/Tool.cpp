#include "Tool.h"

#include <sstream>
#include <istream>


Tool::Tool()
{
}


Tool::~Tool()
{
}

void Tool::splitString(const std::string & input, std::vector<std::string>& output, std::string &delim)
{
	std::string::size_type pos1, pos2;
	pos1 = 0;
	pos2 = input.find(delim);

	while (std::string::npos != pos2)
	{
		output.push_back(input.substr(pos1, pos2 - pos1));

		pos1 = pos2 + delim.size();
		pos2 = input.find(delim, pos1);
	}
	if (pos1 != input.length())
		output.push_back(input.substr(pos1));
}
