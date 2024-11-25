#pragma once
#include <string>
#include <vector>
class StringHelper {
public:
	//returns the next line , including the next line character
	static std::string nextLine(const std::string& str, int32_t& begin) {
		auto i = begin;
		for (; i < str.size(); i++)
		{
			if (str[i] == '\n')
			{
				i++;
				return str.substr(begin, i - begin);
			}
		}
		return "";
	}

	//returns the next line , including the next line character
	static std::vector<char> nextLine(const std::vector<char>& str, int32_t& begin) {
		auto i = begin;
		for (; i < str.size(); i++)
		{
			if (str[i] == '\n')
			{
				i++;
				return std::vector<char>(str.begin() + begin, str.begin() + i);
			}
		}
		return {};
	}
	static std::vector<ByteArray> toByteArrayVec(const std::vector<std::string>& vec) {
		std::vector<ByteArray> newVec(vec.size());

		for (auto i = 0; i < vec.size(); i++) {
			newVec[i] = ByteArray(vec[i].begin(), vec[i].end());
		}
		return newVec;
	}

	static int32_t toString(const ByteArray& arr) {
		int32_t num = 0;
		for (char c : arr) {
			assert(c >= '0' && c <= '9');

			num = num * 10 + int32_t(c - '0');
		}
		return num;
	}

	static void appendToByteArray(ByteArray& arr1, const ByteArray& arr2) {
		arr1.insert(arr1.end(), arr2.begin(), arr2.end());
	}
};
			