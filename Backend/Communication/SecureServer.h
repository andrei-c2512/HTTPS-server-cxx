#pragma once
#include "AbstractServer.h"

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


		asio::error_code ec;
		sslContext.use_certificate_chain_file(certFile , ec);
		if (!ec)
			ConsoleLog::info("Sucessfully loaded certificate file");
		else
		{
			ConsoleLog::error("Failed to load certificate file: " + ec.message());
			abort = true;
		}



		sslContext.use_private_key_file(keyFile, asio::ssl::context::pem , ec);
		if (!ec)
			ConsoleLog::info("Sucessfully loaded private key file");
		else
		{
			ConsoleLog::error("Failed to load private key file: " + ec.message());
			abort = true;
		}

		sslContext.load_verify_file(certFile, ec);
		if (!ec) {
			ConsoleLog::info("Added new file for verification");
		}
		else {
			ConsoleLog::error("Failed to load the certificate file: " + ec.message());
		}
	}


	void listen() override {
		assert(abort == false);

		//I am using a raw pointer here because using smart pointers would actually delete the socket when calling async functions
		SslSocket* socket = new SslSocket(asioContext, sslContext);

		asioAcceptor.async_accept(socket->lowest_layer(),
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
	void startHandshake(SslSocket* socket) {
		socket->async_handshake(asio::ssl::stream_base::server,
			[this , socket](asio::error_code ec) {
			if (!ec) {
				ConsoleLog::info("Handshake sucessful");
				std::shared_ptr<connection> conn =
					std::make_shared<connection>(asioContext, sslContext, std::move(*socket), readQueue);

				list.addNew(conn);
				conn->listen();
				listen();
			}
			else
			{
				ConsoleLog::error("Handshake failed: " + ec.message());
			}
			delete socket;
		});
	}
protected:
	asio::ssl::context sslContext;
	AbstractServer<connection, messageType>::asioAcceptor;
	AbstractServer<connection, messageType>::readQueue;
	AbstractServer<connection, messageType>::list;
	AbstractServer<connection, messageType>::asioContext;
	AbstractServer<connection, messageType>::abort;
};
