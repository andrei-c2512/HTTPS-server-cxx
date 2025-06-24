#pragma once
#include "Thumos/HttpsServer.hpp"
#include "Thumos/Routing/ListRouter.hpp"
#include "AuthServer/HandlingContext.hpp"


class Server : public thm::HttpsServer {
public:
	Server(int32_t port);
protected:
	void onNewMessage(std::shared_ptr<thm::HttpRequest> req) override;
	void initRouter() override;
private:
	ResourceHandling::HandlingContext ctx;
};
