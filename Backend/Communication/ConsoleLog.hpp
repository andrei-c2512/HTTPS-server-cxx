#pragma once
#include "Common.hpp"
#include <iostream>



class ConsoleLog {
public:
	static constexpr int32_t lineLimit = 50;
	static std::string endl() {
		return '\n' + std::string(strlen("[MESSAGE]" + 1), ' ');
	}
	static void message(const std::string_view str) {
		printColoredText("[MESSAGE]", "92");
		writeText(str);
	}
	static void error(const std::string_view str){
		printColoredText("[ERROR]  ", "91");
		writeText(str);
	}
	static void warning(const std::string_view str) {
		printColoredText("[WARNING]", "93");
		writeText(str);
	}
	static void info(const std::string_view str) {
		printColoredText("[INFO]   ", "96");
		writeText(str);
	}

	static void writeText(const std::string_view str) {
		std::string_view nextSequence = str.substr(0, lineLimit);
		nextSequence = nextSequence.substr(0, std::min(nextSequence.find('\n'), (size_t)lineLimit));

		std::cout << ' ' << nextSequence;
		std::cout << '\n';

		int32_t i = nextSequence.size();
		for (; i < str.size(); )
		{
			nextSequence = writeLine(str , i);
			i += nextSequence.size();
			if (nextSequence.size() < lineLimit)
				i++;
		}
	}
	static std::string_view writeLine(const std::string_view str , int32_t& start) {
		std::string_view nextSequence = str.substr(start, lineLimit);
		nextSequence = nextSequence.substr(0, std::min(nextSequence.find('\n'), (size_t)lineLimit));

		std::cout << std::string(strlen("[MESSAGE]"), ' ')
			<< ' ' << nextSequence;

		std::cout << '\n';

		return nextSequence;
	}
	//returns true on error
	static bool handleError(asio::error_code& ec, const std::string_view sucessMsg , const std::string& errorMsg) {
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
	static void printColoredText(const std::string_view msg, const std::string_view color) {
		std::cout << "\033[" << color << "m" << msg << "\033[0m";
	}
};