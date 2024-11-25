#pragma once
#include "Connection.h"
#include "HttpMessage.h"
#include "HttpResponseReader.h"
//if you are a client and want to connect to a server , use this
//this one is is ready to read incoming responses(since clients only need to read responses)


class HttpClientConnection : public Connection<HttpResponse> {
public:
	HttpClientConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<HttpResponse>>& queue)
		:Connection<HttpResponse>(context0, std::move(socket0), queue)
	{
		reader = std::make_shared<HttpResponseReader>();
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
protected:
	std::shared_ptr<HttpResponseReader> reader;
};
