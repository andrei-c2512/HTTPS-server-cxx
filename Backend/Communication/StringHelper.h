#pragma once
#include <string>
#include <vector>
#include "Common.h"


class StringHelper {
public:
	//returns the next line , including the next line character
	static std::string nextLine(const std::string& str, int32_t& begin) {
		auto copy = begin;
		for (; begin < str.size(); begin++)
		{
			if (str[begin] == '\n')
			{
				return str.substr(copy, begin++ - copy);
			}
		}
		return "";
	}
	static std::string nextLine(const std::string& str, int32_t& begin, int32_t end) {
		auto copy = begin;
		for (; begin < end; begin++)
		{
			if (str[begin] == '\n')
			{
				return str.substr(copy, begin++ - copy);
			}
		}
		return "";
	}
};
			