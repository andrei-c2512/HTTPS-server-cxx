#pragma once
#include "HttpsServerSession.hpp"
#include "SecureServer.hpp"
#include "RouterInterface.hpp"
#include "HttpFilter.hpp"

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

		auto result = httpFilter.filter(message->headers());
		std::shared_ptr<HttpResponse> response;
		if (result.first == HttpCommon::StatusCode::CONTINUE) {

			//TO DO: make some sort of class that specifies the requirments for the response(e.g. Accepted formats , encodings etc)
			response = router->handleRequest(message);
		}
		else {
			response = HttpResponse::createErrorResponse(result.second);
		}
		

		list.sendMessage(response , response->userId());
	}

	//you can initialize your router here , set to 0 to force an implementation
	virtual void initRouter() = 0;
private:
	HttpFilter httpFilter;
	std::unique_ptr<RouterInterface> router = nullptr;
	SecureServer<HttpsServerSession, HttpRequest, HttpResponse>::list;
};