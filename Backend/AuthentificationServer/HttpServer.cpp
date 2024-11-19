#include "HttpServer.h"
#include "ConsoleLog.h"

std::string serverTag = "[SERVER]";
std::string errorTag = "[ERROR]";

HttpServer::HttpServer(int16_t port) 
	:asioAcceptor(asioContext , asio::ip::tcp::endpoint(asio::ip::tcp::v4() , port))
{
	
}
void HttpServer::start() {
	try {
		waitForConnections();

		contextThread = std::thread([this]() { asioContext.run();  });
	}
	catch (std::exception& e) {
		ConsoleLog::error(e.what());
	}
	ConsoleLog::message("Server started");
}
void HttpServer::stop() {
	asioContext.stop();

	if (contextThread.joinable()) contextThread.join();

	ConsoleLog::message("Server stopped");
}

void HttpServer::waitForConnections() {

}