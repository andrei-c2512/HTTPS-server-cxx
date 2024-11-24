#pragma once
#include <iostream>

class ConsoleLog {
public:
	static std::string errorTag;
	static std::string serverTag;
	static std::string warningTag;
	static std::string infoTag;

	static void message(const std::string& str);
	static void error(const std::string& str);
	static void warning(const std::string& str);
	static void info(const std::string& str);
};