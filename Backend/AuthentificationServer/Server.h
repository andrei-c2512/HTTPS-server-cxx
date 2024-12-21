#pragma once
#include "HttpsServer.h"
#include "ListRouter.h"

class Server : public HttpsServer {
public:
	Server(int32_t port);
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> req) override;
};
