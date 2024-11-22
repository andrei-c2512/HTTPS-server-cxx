#pragma once
#include <string>
#include <vector>
namespace StringHelper {
	//returns the next line , including the next line character
	std::string nextLine(const std::string& str, int32_t begin = 0) {
		auto i = begin;
		for (; i < str.size(); i++)
		{
			if (str[i] == '\n')
				return str.substr(begin, i + 1- begin);
		}
		return "";
	}

	//returns the next line , including the next line character
	std::vector<char> nextLine(const std::vector<char>& str, int32_t begin = 0) {
		auto i = begin;
		for (; i < str.size(); i++)
		{
			if (str[i] == '\n')
				return std::vector<char>(str.begin() + begin, str.begin() + i + 1);
		}
		return {};
	}
}
			