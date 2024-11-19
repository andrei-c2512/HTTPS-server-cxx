#pragma once
#include <iostream>

namespace ConsoleLog {
	std::string errorTag = "[ERROR]";
	std::string serverTag = "[SERVER]";

	void message(const std::string& str) {
		std::cout << serverTag << ' ' << str;
	}
	void error(const std::string& str) {
		std::cout << errorTag << ' ' << str;
	}
}