#pragma once
#include "HttpServer.h"

class Server : public HttpServer {
public:
	Server(int32_t port);
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> req) override;
};
