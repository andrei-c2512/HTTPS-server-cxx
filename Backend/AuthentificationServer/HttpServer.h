#pragma once
#include "asio.hpp"
#include "TsQueue.h"
#include "HttpRequest.h"
#include <iostream>

class HttpServer {
public:
	HttpServer(int16_t port);
	void start();
	void stop();

	void waitForConnections();
private:
	asio::io_context asioContext;
	std::thread contextThread;

	asio::ip::tcp::acceptor asioAcceptor;
};