#pragma once
#include "AbstractClient.h"
#include "HttpResponse.h"
#include "HttpClientConnection.h"

class HttpClient : public AbstractClient<HttpResponse, HttpRequest , HttpClientConnection> {
public:
	using AbstractClient::AbstractClient;
};