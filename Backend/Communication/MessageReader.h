#pragma once
#include "Common.h"


enum class ReadStatus {
	//would've used error but there is a macro named like that
	FAILURE,
	IDLE,
	SUCCESS
};

enum class ReadLoopStatus {
	FAILURE = 0x0,
	CONTINUE = 0x1,
	SUCCESS = 0x2
};

class MessageReader {
public:
	MessageReader() = default;
	virtual void start(asio::ip::tcp::socket& socket) = 0;
	virtual std::string messageString() const = 0;
	bool ready() const noexcept { return _ready; }
protected:
	bool _ready = false;
};