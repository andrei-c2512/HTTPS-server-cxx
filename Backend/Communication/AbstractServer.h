#pragma once
#include "Common.h"
#include "ServerConnectionList.h"
#include "ConsoleLog.h"


template<typename connection, typename messageType>
class AbstractServer {
public:
	AbstractServer(int16_t port)
		:asioAcceptor(asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
	{}
	virtual ~AbstractServer() {
		onStop();
		asioContext.stop();

		if (contextThread.joinable()) contextThread.join();

		//I would just call stop() but for some reason it causes a linker error here because of ConsoleLog ? tf
	}
	void start() {
		try {
			listen();
			onStart();
			contextThread = std::thread([this]() { asioContext.run();  });
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());
		}

		ConsoleLog::message("Server started");
	}
	void stop() {
		onStop();
		asioContext.stop();

		if (contextThread.joinable()) contextThread.join();

		ConsoleLog::message("Server stopped");
	}

	void listen() {
		asioAcceptor.async_accept( 
			[this](std::error_code ec, asio::ip::tcp::socket socket) {
				if (!ec) {
					ConsoleLog::message("New connection");
					std::shared_ptr<HttpServerConnection> conn = std::make_shared<HttpServerConnection>(asioContext, std::move(socket), readQueue);
					list.addNew(conn);
				}
				else {
					ConsoleLog::error("Connection error: " + ec.message());
				}
				listen();
			}
		);
	}

	void update() {
		while (readQueue.empty() == false) {
			auto request = readQueue.front();
			readQueue.pop_front();
			onNewMessage(request);
		}
	}
protected:
	virtual void onNewMessage(std::shared_ptr<messageType> message) {}
	virtual void onNewConnection(std::shared_ptr<connection> connection) {}
	virtual void onStop() {}
	virtual void onStart() {}
protected:
	asio::io_context asioContext;
	std::thread contextThread;

	asio::ip::tcp::acceptor asioAcceptor;
	TsQueue<std::shared_ptr<messageType>> readQueue;
	ServerConnectionList<connection> list;
};
