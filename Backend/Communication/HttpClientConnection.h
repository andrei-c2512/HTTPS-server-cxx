#pragma once
#include "BasicConnection.h"
#include "HttpMessage.h"
#include "HttpResponseReader.h"
#include "HttpRequest.h"
//if you are a client and want to connect to a server , use this
//this one is is ready to read incoming responses(since clients only need to read responses)


class HttpClientConnection : public BasicConnection<HttpResponse, HttpRequest>{
public:
	HttpClientConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<HttpResponse>>& queue)
		:BasicConnection<HttpResponse, HttpRequest>(context0, std::move(socket0), queue)
	{
		reader = new HttpResponseReader<asio::ip::tcp::socket>(readQueue);
	}
protected:
	using BasicConnection<HttpResponse, HttpRequest>::reader;
	using BasicConnection<HttpResponse, HttpRequest>::readQueue;
};
