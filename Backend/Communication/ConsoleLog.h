#pragma once
#include <iostream>

namespace ConsoleLog {
	std::string errorTag = "[ERROR]";
	std::string serverTag = "[SERVER]";
	std::string warningTag = "[WARNING]";
	std::string infoTag = "[INFO]";
	void message(const std::string& str) {
		std::cout << serverTag << ' ' << str;
	}
	void error(const std::string& str) {
		std::cout << errorTag << ' ' << str;
	}
	void warning(const std::string& str) {
		std::cout << warningTag << ' ' << str;
 	}
	void info(const std::string& str) {
		std::cout << infoTag << ' ' << str;
	}
}