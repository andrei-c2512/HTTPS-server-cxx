#include "Server.h"

Server::Server(int32_t port)
	:HttpsServer(port,
		"C:/Users/Andrei C/security/ca.crt",
		"C:/Users/Andrei C/security/ca.key")
{}
void Server::onNewMessage(std::shared_ptr<HttpRequest> req) {
	ConsoleLog::info(req->toString());
}
