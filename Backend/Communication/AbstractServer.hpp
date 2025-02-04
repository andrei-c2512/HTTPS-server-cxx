#pragma once
#include "Common.hpp"
#include "ServerConnectionList.hpp"
#include "ConsoleLog.hpp"



template<typename connection, typename messageTypeIn , typename messageTypeOut>
class AbstractServer {
public:
	AbstractServer(int16_t port)
		:asioAcceptor(asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
	{}
	virtual ~AbstractServer() {
		stop();
	}
	virtual void start() {
		if (abort) {
			ConsoleLog::error("Server is COOKED , cannot start");
			return;
		}
		try {
			listen();
			ConsoleLog::message("Listening...");
			onStart();
			contextThread = std::thread([this]() { 
				asioContext.run(); 
				});
			
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());
		}

		ConsoleLog::message("Server started");
	}
	virtual void stop() {
		if (stopped == false) {
			onStop();
			asioContext.stop();

			if (contextThread.joinable()) contextThread.join();

			ConsoleLog::message("Server stopped");
			stopped = true;
		}
	}
	virtual void listen() {}

	void update(){
		while (readQueue.empty() == false) {
			auto request = readQueue.front();
			readQueue.pop_front();
			ConsoleLog::info("Processing new message...");
			onNewMessage(request);
		}
	}
protected:
	virtual void onNewMessage(std::shared_ptr<messageTypeIn> message) {}
	virtual void onNewConnection(std::shared_ptr<connection> connection) {}
	virtual void onStop() {}
	virtual void onStart() {}
protected:
	asio::io_context asioContext;
	std::thread contextThread;

	asio::ip::tcp::acceptor asioAcceptor;
	TsQueue<std::shared_ptr<messageTypeIn>> readQueue;
	ServerConnectionList<connection , messageTypeOut> list;

	//the abort flag will be used by super classes when some condition for starting isn't met
	// ex: failed to set certificate for a secure server
	bool abort = false;
	bool stopped = false;
};
