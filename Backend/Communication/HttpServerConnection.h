#pragma once
#include "HttpMessage.h"
#include "BasicConnection.h"
#include "HttpRequestReader.h"
#include "HttpResponse.h"

//if you are a server and want to handle connections from clients , use this
//this one is ready to read incoming requests(since servers respond to requests)


class HttpServerConnection : public BasicConnection<HttpRequest , HttpResponse> {
public:
	HttpServerConnection(asio::io_context& context0, BasicSocket socket0, TsQueue<std::shared_ptr<HttpRequest>>& queue)
		:BasicConnection<HttpRequest , HttpResponse>(context0, std::move(socket0), queue)
	{
		// a Http reader of type unsafe socket
		reader = new HttpRequestReader<BasicSocket>(queue);
	}
protected:
	using BasicConnection<HttpRequest, HttpResponse>::socket;
	using BasicConnection<HttpRequest, HttpResponse>::reader;
};
