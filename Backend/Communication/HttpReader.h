#pragma once
#include "rapidjson/document.h"
#include <string>
#include <map>
#include <array>
#include "MessageReader.h"
#include "asio.hpp"
#include <vector>

class HttpReader : public MessageReader {
public:
	HttpReader();
	
	void start(asio::ip::tcp::socket& socket) override;
protected:
	void readHeader(asio::ip::tcp::socket& socket);
	void readBody(asio::ip::tcp::socket& socket);
	void processHeaderLine(const std::vector<char>& buf);
private:
	std::map<std::string, std::string> headers;
	rapidjson::Document d;
	std::array<std::string, 3> reqTypeStorage;

	std::vector<char> unfinishedMessage;
	std::vector<char> unfinishedLine;
	std::vector<char> buffer;

	int32_t bufferSize;
};