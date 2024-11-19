#include "HttpRequest.h"
#include "StringHelper.h"

HttpRequest::HttpRequest(const std::string& str) {
	int32_t i = 0;
	int32_t strCursor = 0;
	int32_t last = 0;

	char breakChar = ' ';
	for (; strCursor < str.size(); strCursor++) {
		if (str[strCursor] == breakChar)
		{
			reqTypeStorage[i] = str.substr(last, i - last);
			last = i + 1;
			i++;
			if (i == 2)
				breakChar = '\n';
			else if (i == 3)
				break;
		}
	}
	extractHeaders(str, strCursor);
}

int32_t HttpRequest::extractHeaders(const std::string& str, int32_t start) {
	char ch = str[start];
	char startOfJson = '{';

	while (ch != startOfJson) {
		//i would use std::istringstream to read line by line but I don't want to make a copy of the string
		std::string line = StringHelper::nextLine(str, start);
		start += line.size();
	}

	return start;
}

std::string HttpRequest::method() const noexcept { return reqTypeStorage[0]; }
std::string HttpRequest::url() const noexcept { return reqTypeStorage[1]; }
std::string HttpRequest::version() const noexcept { return reqTypeStorage[2]; };
std::string HttpRequest::scheme() const noexcept { return ""; }
std::string HttpRequest::server() const noexcept { return ""; }
std::string HttpRequest::path() const noexcept { return ""; }
