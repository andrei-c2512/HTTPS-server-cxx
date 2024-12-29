#pragma once
#include "HttpServerConnection.h"
#include "BasicServer.h"
#include "ListRouter.h"

/*
	How the server works:
		-when it starts , it listens for connections and adds them to the connection list
		-if you call listen() it starts listening for messages
		-every connection has a reference to the incoming messages queue from the server. Every connection handles incoming data
		from their own socket and adds it to the message queue. 
*/


class HttpServer : public BasicServer<HttpServerConnection, HttpRequest , HttpResponse> {
public:
	HttpServer(int16_t port)
		:BasicServer<HttpServerConnection, HttpRequest , HttpResponse>(port)
	{}
	//no need to manage memory
	void setRouter(std::unique_ptr<RouterInterface> router0) {
		router = std::move(router0);
	}
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> message) override {
		assert(router && "Please provide a router. You can set it with setRouter() function");
		std::shared_ptr<HttpResponse> response = router->handleRequest(message);
		list.sendMessage(response, response->userId());
	}
	//you can initialize your router here , set to 0 to force an implementation
	virtual void initRouter() = 0;
private:
	std::unique_ptr<RouterInterface> router = nullptr;
	BasicServer<HttpServerConnection, HttpRequest, HttpResponse>::list;
}; 
