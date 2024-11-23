#pragma once
#include <string>


class MessageReader {
public:
	MessageReader() = default;
	virtual bool start(asio::ip::tcp::socket& socket) = 0;
};