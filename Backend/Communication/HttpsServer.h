#pragma once
#include "HttpsServerSession.h"
#include "SecureServer.h"

class HttpsServer : public SecureServer<HttpsServerSession , HttpRequest> {
public:
	HttpsServer(int16_t port, const std::string& certFile, const std::string& keyFile)
		:SecureServer<HttpsServerSession, HttpRequest>(port , certFile , keyFile)
	{}
private:
};