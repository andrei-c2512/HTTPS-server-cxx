#pragma once
#include "BasicConnection.hpp"
#include "HttpMessage.hpp"
#include "HttpResponseReader.hpp"
#include "HttpRequest.hpp"
//if you are a client and want to connect to a server , use this
//this one is is ready to read incoming responses(since clients only need to read responses)


class HttpClientConnection : public BasicConnection<HttpResponse, HttpRequest>{
public:
	HttpClientConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<HttpResponse>>& queue)
		:BasicConnection<HttpResponse, HttpRequest>(context0, std::move(socket0), queue)
	{
		reader = new HttpResponseReader<BasicSocket>(_canWrite  , readQueue);
	}
protected:
	using BasicConnection<HttpResponse, HttpRequest>::reader;
	using BasicConnection<HttpResponse, HttpRequest>::readQueue;
};
