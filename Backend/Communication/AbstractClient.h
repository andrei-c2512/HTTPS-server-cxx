#pragma once
#include "Connection.h"
#include "asio.hpp"

//shit's wild , so basically
/*
	client -> needs something of type message
		   -> a type of connection that takes said message
*/

template<message messageType, connection<messageType> connectionType>
class AbstractClient {
public:
	AbstractClient() {

	}
	void connect(const std::string& host, int16_t port) {
		try {
			conn = std::make_shared<connectionType>(context , asio::ip::tcp::socket(context) , readQueue);
			conn->connect(host, port);

			contextThread = std::thread([this]() {
				context.run();
				});
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());

		}
	}
	void disconnect() {
		conn->disconnect();
	}
	bool isConnected() const noexcept { return conn->isConnected(); }

	void send(std::shared_ptr<messageType> msg) {
		conn->send(msg);
	}
protected:
	asio::io_context context;
	std::thread contextThread;

	TsQueue<messageType> readQueue;

	std::shared_ptr<connectionType> conn;
};
