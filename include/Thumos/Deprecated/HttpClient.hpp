#pragma once
#include "BasicClient.hpp"
#include "HttpResponse.hpp"
#include "HttpClientConnection.hpp"

class HttpClient : public BasicClient<HttpResponse, HttpRequest , HttpClientConnection> {
public:
	using BasicClient::BasicClient;
};