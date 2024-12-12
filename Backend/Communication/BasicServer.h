#pragma once
#include "Common.h"
#include "ServerConnectionList.h"
#include "ConsoleLog.h"
#include "AbstractServer.h"

//will only work for connection classes that use BasicSocket
template<typename connection, typename messageType>
class BasicServer : public AbstractServer<connection , messageType>{
public:
	BasicServer(int16_t port)
		:AbstractServer<connection, messageType>(port)
	{}
	

	void listen() override{
		asioAcceptor.async_accept(
			[this](std::error_code ec, asio::ip::tcp::socket socket) {
				ConsoleLog::message("Listening...");
				if (!ec) {
					ConsoleLog::info("New connection");
					std::shared_ptr<connection> conn = std::make_shared<connection>(asioContext, std::move(socket), readQueue);
					list.addNew(conn);
					conn->listen();
				}
				else {
					ConsoleLog::error("Connection error: " + ec.message());
				}
				listen();
			}
		);
	}
	AbstractServer<connection, messageType>::update;
	AbstractServer<connection, messageType>::stop;
	AbstractServer<connection, messageType>::start;
protected:
	AbstractServer<connection, messageType>::asioAcceptor;
	AbstractServer<connection, messageType>::readQueue;
	AbstractServer<connection, messageType>::list;
	AbstractServer<connection, messageType>::asioContext;
};
