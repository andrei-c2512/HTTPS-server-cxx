#pragma once
#include "HttpMessage.h"
#include "Connection.h"
#include "HttpRequestReader.h"
#include "HttpResponse.h"

//if you are a server and want to handle connections from clients , use this
//this one is ready to read incoming requests(since servers respond to requests)


class HttpServerConnection : public Connection<HttpRequest , HttpResponse> {
public:
	HttpServerConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<HttpRequest>>& queue)
		:Connection<HttpRequest , HttpResponse>(context0, std::move(socket0), queue)
	{
		reader = std::make_shared<HttpRequestReader>(readQueue);
	}
	void listen() override {
		//ConsoleLog::info("New connection with an id of " + std::to_string(_id) + " started listening");
		reader->start(socket);
	}
	void writeMessage(std::shared_ptr<HttpResponse> msg) override {
		
	}
protected:
	std::shared_ptr<HttpRequestReader> reader;
	ReadLoopStatus go = ReadLoopStatus::CONTINUE;
};
