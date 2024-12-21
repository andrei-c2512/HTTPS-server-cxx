#pragma once
#include "Common.h"
#include <iostream>



class ConsoleLog {
public:
	static void message(const std::string_view& str) {
		printColoredText("[MESSAGE]", "92");
		std::cout << ' ' << str << '\n';
	}
	static void error(const std::string_view& str){
		printColoredText("[ERROR]", "91");
		std::cout << ' ' << str << '\n';
	}
	static void warning(const std::string_view& str) {
		printColoredText("[WARNING]", "93");
		std::cout << ' ' << str << '\n';
	}
	static void info(const std::string_view& str) {
		printColoredText("[INFO]", "96");
		std::cout << ' ' << str << '\n';
	}
	//returns true on error
	static bool handleError(asio::error_code& ec, const std::string_view& sucessMsg , const std::string& errorMsg) {
		if (!ec) {
			ConsoleLog::info(sucessMsg);
			return false;
		}
		else
		{
			ConsoleLog::error(errorMsg + " : " + ec.message());
			return true;
		}
	}
private:
	static void printColoredText(const std::string_view& msg, const std::string_view& color) {
		std::cout << "\033[" << color << "m" << msg << "\033[0m";
	}
};