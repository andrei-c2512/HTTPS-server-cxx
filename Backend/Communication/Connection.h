#pragma once
#include "TsQueue.h"
#include "asio.hpp"
#include "Message.h"

class Connection {
public:
	Connection() = default;
public:
	bool connect();
	bool disconnect();
	bool isConnected() const;
public:
	void write(std::shared_ptr<Message> msg);
protected:
	asio::ip::tcp::socket socket;
	asio::io_context& context;
	TsQueue<std::shared_ptr<Message>> writeQueue;
	TsQueue<std::shared_ptr<Message>>& readQueue;
};