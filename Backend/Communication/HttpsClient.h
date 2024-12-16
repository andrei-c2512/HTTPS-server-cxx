#pragma once
#include "SecureClient.h"
#include "HttpsClientConnection.h"

class HttpsClient : public SecureClient<HttpResponse, HttpRequest, HttpsClientConnection> {
public:
	HttpsClient(const std::string& publicKeyPath)
		:SecureClient<HttpResponse, HttpRequest, HttpsClientConnection>(publicKeyPath)
	{}
};