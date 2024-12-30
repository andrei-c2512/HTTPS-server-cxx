#pragma once
#include "SecureConnection.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpRequestReader.hpp"

class HttpsServerSession : public SecureConnection<HttpRequest, HttpResponse> {
public:
	HttpsServerSession(asio::io_context& context0, asio::ssl::context& sslContext,
		asio::ssl::stream<BasicSocket> stream,
		TsQueue<std::shared_ptr<HttpRequest>>& queue0)
		: SecureConnection<HttpRequest, HttpResponse>(context0, sslContext, std::move(stream), queue0)
	{
		reader = new HttpRequestReader<SslSocket>(_canWrite, queue0);
	}
};