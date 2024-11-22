#pragma once
#include <string>


class MessageReader {
public:
	MessageReader() = default;
	virtual void start(asio::ip::tcp::socket& socket);
};