#pragma once
#include "Common.h"



class MessageReader {
public:
	MessageReader() = default;
	virtual bool start(asio::ip::tcp::socket& socket) = 0;
	virtual ByteArray messageByteArray() const = 0;
	virtual std::string messageString() const = 0;
};