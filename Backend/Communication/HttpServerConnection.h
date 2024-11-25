#pragma once
#include "HttpMessage.h"
#include "Connection.h"
#include "HttpRequestReader.h"

//if you are a server and want to handle connections from clients , use this
//this one is ready to read incoming requests(since servers respond to requests)


class HttpServerConnection : public Connection<HttpRequest> {
public:
	HttpServerConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<HttpRequest>>& queue)
		:Connection<HttpRequest>(context0, std::move(socket0), queue)
	{
		reader = std::make_shared<HttpRequestReader>();
	}
	void listen() override {
		asio::post(context, [this]() {
			bool go = true;
			while (go)
			{
				go = reader->start(socket);
			}
			//for error handling here maybe?

			});
	}
	void writeMessage(std::shared_ptr<HttpRequest> msg) override {

	}
protected:
	std::shared_ptr<HttpRequestReader> reader;
};
