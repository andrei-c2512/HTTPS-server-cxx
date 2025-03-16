#pragma once
#include "AbstractServer.hpp"

//will only work for connection classes that use SslSocket
template<typename connection, typename messageTypeIn , typename messageTypeOut>
class SecureServer : public AbstractServer<connection, messageTypeIn , messageTypeOut> {
public:
	SecureServer(int16_t port , const std::string& certFile , const std::string& keyFile , std::vector<std::string> approvedCerts)
		:AbstractServer<connection, messageTypeIn , messageTypeOut>(port) , sslContext(asio::ssl::context::sslv23)
	{
		sslContext.set_options(asio::ssl::context::default_workarounds |
			asio::ssl::context::no_sslv2 |
			asio::ssl::context::single_dh_use);


		asio::error_code ec;
		sslContext.use_certificate_chain_file(certFile , ec);
	
		abort = abort || ConsoleLog::handleError(ec, "Sucessfully loaded certificate file", "Failed to load certificate file");

		sslContext.use_private_key_file(keyFile, asio::ssl::context::pem , ec);
		abort = abort || ConsoleLog::handleError(ec, "Sucessfully loaded private key file", "Failed to load private key file");

		for (const std::string& filePath : approvedCerts) {
			sslContext.load_verify_file(filePath, ec);
			abort = abort || ConsoleLog::handleError(ec, "Added new file for verification", "Failed to load the certificate file");
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
	AbstractServer<connection, messageTypeIn , messageTypeOut>::update;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::stop;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::start;
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
			}
			else
			{
				ConsoleLog::error("Handshake failed: " + ec.message());
			}
			delete socket;
			listen();
		});
	}
protected:
	virtual void onNewMessage(std::shared_ptr<messageTypeIn> message) override {}
	virtual void onNewConnection(std::shared_ptr<connection> connection) override {}
	virtual void onStop() override {}
	virtual void onStart() override {}
protected:
	asio::ssl::context sslContext;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::asioAcceptor;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::readQueue;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::list;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::asioContext;
	AbstractServer<connection, messageTypeIn , messageTypeOut>::abort;
};
