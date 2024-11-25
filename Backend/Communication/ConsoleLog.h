#pragma once
#include "Common.h"
#include <iostream>

class ConsoleLog {
public:
	static void message(const std::string_view& str) {
		std::cout << "[MESSAGE]" << ' ' << str;
	}
	static void error(const std::string_view& str){
		std::cout << "[ERROR]" << ' ' << str;
	}
	static void warning(const std::string_view& str) {
		std::cout << "[WARNING]" << ' ' << str;
	}
	static void info(const std::string_view& str) {
		std::cout << "[INFO]" << ' ' << str;
	}
};