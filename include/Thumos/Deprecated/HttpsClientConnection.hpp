#pragma once
#include "SecureConnection.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "HttpResponseReader.hpp"


class HttpsClientConnection : public SecureConnection<HttpResponse , HttpRequest> {
public:
	HttpsClientConnection(asio::io_context& context0, asio::ssl::context& sslContext , SslSocket socket0, TsQueue<std::shared_ptr<HttpResponse>>& queue)
		:SecureConnection<HttpResponse, HttpRequest>(context0, sslContext, std::move(socket0), queue)
	{
		reader = new HttpResponseReader<SslSocket>(_canWrite, readQueue);
	}
};