#pragma once
#include <string>

namespace StringHelper {
	std::string nextLine(const std::string& str, int32_t begin) {
		auto i = begin;
		for (; i < str.size(); i++)
		{
			if (str[i] == '\n')
				return str.substr(begin, i - begin);
		}
		return "";
	}
}