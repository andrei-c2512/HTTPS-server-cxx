#pragma once
#include "asio.hpp"
#include "TsQueue.h"
#include "HttpRequest.h"
#include <iostream>
#include "ConnectionList.h"

class HttpServer {
public:
	HttpServer(int16_t port);
	void start();
	void stop();

	void listen();
	void update();

private:
	asio::io_context asioContext;
	std::thread contextThread;

	asio::ip::tcp::acceptor asioAcceptor;
	TsQueue<std::shared_ptr<Message>> readQueue;
	ConnectionList list;
};