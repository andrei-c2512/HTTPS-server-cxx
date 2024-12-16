#pragma once
#include "BasicClient.h"
#include "HttpResponse.h"
#include "HttpClientConnection.h"

class HttpClient : public BasicClient<HttpResponse, HttpRequest , HttpClientConnection> {
public:
	using BasicClient::BasicClient;
};