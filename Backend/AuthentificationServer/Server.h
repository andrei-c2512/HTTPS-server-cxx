#pragma once
#include "asio.hpp"
#include "TsQueue.h"
#include "HttpRequest.h"
#include <iostream>
#include "ServerConnectionList.h"
#include "HttpClientConnection.h"
#include "HttpServer.h"

class Server : public HttpServer {
public:
	Server(int32_t port);
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> req) override;
};