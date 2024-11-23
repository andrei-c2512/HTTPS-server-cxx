#pragma once
#include "TsQueue.h"
#include "asio.hpp"
#include "Message.h"
#include "HttpReader.h"
class Connection {
public:
	enum class Type {
		TCP, //  for custom messages
		Http,
		Https
	};
public:
	Connection(asio::io_context& context0 , asio::ip::tcp::socket socket0 , TsQueue<std::shared_ptr<Message>>& queue);
	Connection& operator=(const Connection&) = delete;
	Connection(const Connection&) = delete;
public:
	bool connect(const std::string& host , int16_t port);
	bool disconnect();
	bool isConnected() const;
	void setId(int32_t id0);

	int32_t id() const noexcept;
	//listens for data
	virtual void listen() = 0;
public:
	void write(std::shared_ptr<Message> msg);
protected:
	virtual void initMsgReader() = 0;
protected:
	asio::ip::tcp::socket socket;
	asio::io_context& context;
	TsQueue<std::shared_ptr<Message>> writeQueue;
	TsQueue<std::shared_ptr<Message>>& readQueue;

	int32_t _id;
};
