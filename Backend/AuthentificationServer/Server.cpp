#include "Server.h"

Server::Server(int32_t port)
	:HttpsServer(port,
		"C:/Users/Andrei C/security/ca.crt",
		"C:/Users/Andrei C/security/ca.key", std::vector<std::string>(1, "C:/Users/Andrei C/security/ca.crt"))
{
	auto router = std::make_unique<ListRouter>();
	router->addRoute("/", [](std::shared_ptr<HttpRequest> request){

		HttpHeaders headers;
		headers.add(HttpCommon::Header::CONTENT_TYPE, "json");
		headers.add(HttpCommon::Header::CONTENT_LENGTH, "0");


		auto response = std::make_shared<HttpResponse>( 200 , "OK" , std::move(headers));
		return nullptr;
	});
	setRouter(std::move(router));
}
void Server::onNewMessage(std::shared_ptr<HttpRequest> req) {
	HttpsServer::onNewMessage(req);
	ConsoleLog::info(req->toString());
}
