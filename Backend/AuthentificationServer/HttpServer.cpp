#include "HttpServer.h"
#include "ConsoleLog.h"



HttpServer::HttpServer(int16_t port) 
	:asioAcceptor(asioContext , asio::ip::tcp::endpoint(asio::ip::tcp::v4() , port))
{
	
}
void HttpServer::start() {
	try {
		listen();

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

void HttpServer::listen() {
	asioAcceptor.async_accept(
		[this](std::error_code ec , asio::ip::tcp::socket& socket) {
			if (!ec) {
				ConsoleLog::message("New connection");
				std::shared_ptr<Connection> conn = std::make_shared<Connection>(asioContext, std::move(socket) , readQueue);
				list.addNew(conn);
			}
			else {
				ConsoleLog::error("Connection error: " + ec.message());
			}
			listen();
		}
	);
}

void HttpServer::update() {
	while (readQueue.empty() == false) {
		auto request = readQueue.front();
		readQueue.pop_front();

	}
}