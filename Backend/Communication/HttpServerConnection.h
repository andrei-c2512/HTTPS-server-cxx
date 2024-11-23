#pragma once
#include "asio.hpp"
#include "TsQueue.h"
#include "HttpRequest.h"
#include <iostream>
#include "Connection.h"


//if you are a server and want to handle connections from clients , use this
//this one is ready to read incoming requests(since servers respond to requests)
class HttpServerConnection : public Connection {
public:
	HttpServerConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<Message>>& queue);
	void listen() override;
protected:
	void initMsgReader() override;
protected:
	std::unique_ptr<MessageReader> reader;
};


