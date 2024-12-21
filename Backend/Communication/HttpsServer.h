#pragma once
#include "HttpsServerSession.h"
#include "SecureServer.h"
#include "RouterInterface.h"

class HttpsServer : public SecureServer<HttpsServerSession , HttpRequest, HttpResponse> {
public:
	HttpsServer(int16_t port, const std::string& certFile, const std::string& keyFile , std::vector<std::string> approvedList)
		:SecureServer<HttpsServerSession, HttpRequest, HttpResponse>(port , certFile , keyFile , std::move(approvedList))
	{}
	void setRouter(std::unique_ptr<RouterInterface> router0) {
		router = std::move(router0);
	}
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> message) override {
		assert(router && "Please provide a router. You can set it with setRouter() function");
		std::shared_ptr<HttpResponse> response = router->handleRequest(message->URI(), message);
		list.sendMessage(response , response->userId());
	}
private:
	std::unique_ptr<RouterInterface> router = nullptr;
	SecureServer<HttpsServerSession, HttpRequest, HttpResponse>::list;
};