#pragma once
#include "Connection.h"
#include "HttpMessage.h"
#include "HttpResponseReader.h"
#include "HttpRequest.h"
//if you are a client and want to connect to a server , use this
//this one is is ready to read incoming responses(since clients only need to read responses)


class HttpClientConnection : public Connection<HttpResponse , HttpRequest> {
public:
	HttpClientConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<HttpResponse>>& queue)
		:Connection<HttpResponse, HttpRequest>(context0, std::move(socket0), queue)
	{
		reader = std::make_shared<HttpResponseReader>(readQueue);
	}
	void listen() override {
		reader->start(socket);
	}
	void writeMessage(std::shared_ptr<HttpRequest> msg) override{
		std::string str = msg->toString();
		//since asio handles chunking huge messages , I don't need to implement that.
		asio::async_write(socket, asio::buffer(str.data(), str.size()),
			[this](std::error_code ec , std::size_t length) {
				if (!ec) {
					writeQueue.pop_front();
					ConsoleLog::info("Sucessfully wrote a request to the server");
					ConsoleLog::info("Request size: " + std::to_string(length));
				}
				else
					ConsoleLog::error("Failed to write a request to the server");
			});
	}
protected:
	std::shared_ptr<HttpResponseReader> reader;
	ReadLoopStatus go = ReadLoopStatus::CONTINUE;
};
