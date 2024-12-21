#pragma once
#include "Common.h"
#include "ServerConnectionList.h"
#include "ConsoleLog.h"
#include "AbstractServer.h"

//will only work for connection classes that use BasicSocket
template<typename connection, typename messageTypeIn , typename messageTypeOut>
class BasicServer : public AbstractServer<connection , messageTypeIn , messageTypeOut>{
public:
	BasicServer(int16_t port)
		:AbstractServer<connection, messageTypeIn , messageTypeOut>(port)
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
	AbstractServer<connection, messageTypeIn , messageTypeOut>::update;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::stop;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::start;
protected:
	AbstractServer<connection, messageTypeIn , messageTypeOut>::asioAcceptor;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::readQueue;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::list;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::asioContext;
};
