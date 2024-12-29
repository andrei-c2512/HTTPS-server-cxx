#pragma once
#include "Common.h"
#include <iostream>



class ConsoleLog {
public:
	static void message( std::string_view str) {
		printColoredText("[MESSAGE]", "92");
		std::cout << ' ' << str << '\n';
	}
	static void error(std::string_view str){
		printColoredText("[ERROR]", "91");
		std::cout << ' ' << str << '\n';
	}
	static void warning(std::string_view str) {
		printColoredText("[WARNING]", "93");
		std::cout << ' ' << str << '\n';
	}
	static void info(std::string_view str) {
		printColoredText("[INFO]", "96");
		std::cout << ' ' << str << '\n';
	}
	//returns true on error
	static bool handleError(asio::error_code& ec, std::string_view sucessMsg , const std::string& errorMsg) {
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
	static void printColoredText(std::string_view msg, std::string_view color) {
		std::cout << "\033[" << color << "m" << msg << "\033[0m";
	}
};