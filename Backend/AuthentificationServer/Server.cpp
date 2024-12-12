#include "Server.h"

Server::Server(int32_t port)
	:HttpServer(port)
{}
void Server::onNewMessage(std::shared_ptr<HttpRequest> req) {
	ConsoleLog::info(req->toString());
}
