#pragma once
#include "HttpsServer.hpp"
#include "ListRouter.hpp"
#include "HandlingContext.hpp"

class Server : public HttpsServer {
public:
	Server(int32_t port);
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> req) override;
	void initRouter() override;
private:
	ResourceHandling::HandlingContext ctx;
};
