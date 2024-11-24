#include "ConsoleLog.h"

std::string ConsoleLog::errorTag = "[ERROR]";
std::string ConsoleLog::serverTag = "[SERVER]";
std::string ConsoleLog::warningTag = "[WARNING]";
std::string ConsoleLog::infoTag = "[INFO]";


void ConsoleLog::message(const std::string& str) {
	std::cout << serverTag << ' ' << str;
}
void ConsoleLog::error(const std::string& str) {
	std::cout << errorTag << ' ' << str;
}
void ConsoleLog::warning(const std::string& str) {
	std::cout << warningTag << ' ' << str;
}
void ConsoleLog::info(const std::string& str) {
	std::cout << infoTag << ' ' << str;
}