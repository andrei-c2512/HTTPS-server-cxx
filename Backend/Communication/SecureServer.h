#pragma once
#include "AbstractServer.h"
#include "ConsoleLog.h"

//will only work for connection classes that use SslSocket
template<typename connection, typename messageType>
class SecureServer : public AbstractServer<connection, messageType> {
public:
	SecureServer(int16_t port , const std::string& certFile , const std::string& keyFile)
		:AbstractServer<connection, messageType>(port) , sslContext(asio::ssl::context::sslv23)
	{
		sslContext.set_options(asio::ssl::context::default_workarounds |
			asio::ssl::context::no_sslv2 |
			asio::ssl::context::single_dh_use);

		sslContext.use_certificate_chain_file(certFile);
		sslContext.use_private_key_file(keyFile, asio::ssl::context::pem);
	}


	void listen() override {
		auto socket = SslSocket(asioContext, sslContext);
		asioAcceptor.async_accept(socket->lowestLayer(),
			[this, socket](asio::error_code ec) {
				if (!ec) {
					ConsoleLog::info("New connection");
					startHandshake(socket);
				}
				else {
					ConsoleLog::error("Connection error: " + ec.message());
				}
			});
	}
	AbstractServer<connection, messageType>::update;
	AbstractServer<connection, messageType>::stop;
	AbstractServer<connection, messageType>::start;
protected:
	void startHandshake(SslSocket& socket) {
		socket->async_handshake(asio::ssl::stream_base::server,
			[socket](asio::error_code ec) {
			if (!ec) {
				ConsoleLog::info("Handshake sucessful");
				std::shared_ptr<connection> conn =
					std::make_shared<connection>(asioContext, sslContext, std::move(socket), readQueue);

				list.addNew(conn);
				conn->listen();
			}
			else
			{
				ConsoleLog::error("Handshake failed: " + ec.message());
			}
		});
	}
protected:
	asio::ssl::context sslContext;
	AbstractServer<connection, messageType>::asioAcceptor;
	AbstractServer<connection, messageType>::readQueue;
	AbstractServer<connection, messageType>::list;
	AbstractServer<connection, messageType>::asioContext;
};
