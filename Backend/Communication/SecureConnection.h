#pragma once
#include "AbstractConnection.h"
#include "asio/ssl.hpp"

template<message messageTypeIn, message messageTypeOut>
class SecureConnection : public AbstractConnection<messageTypeIn, messageTypeOut , SslSocket> {
public:
	SecureConnection(asio::io_context& context0, asio::ssl::context& sslContext,
		SslSocket stream,
		TsQueue<std::shared_ptr<messageTypeIn>>& queue0)
		:AbstractConnection<messageTypeIn, messageTypeOut , SslSocket>(context0, queue0),
		ssl_stream(std::move(stream)), sslContext(sslContext)
	{
		//subclasses should instantiate their reader here
		// I do not want the reader to be set from the constructor , I think it's ugly design in this case
		// unlesss you want some custom reader , which I should add the setting for(because , well , there will be encrypted
		// readings and perhaps you want anything other than the default encryption)
	}
	//deleting cause I don't see the use
	SecureConnection& operator=(const SecureConnection&) = delete;
	SecureConnection(const SecureConnection&) = delete;
	virtual ~SecureConnection() {
	}
public:
	bool connect(const std::string& host, int16_t port) {
		try {
			asio::ip::tcp::resolver resolver(context);
			asio::ip::tcp::resolver::results_type endpoint = resolver.resolve(host, std::to_string(port));


			asio::connect(ssl_stream.lowest_layer(), endpoint);
			ssl_stream.handshake(asio::ssl::stream_base::client);
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());
			return false;
		}
	}
	void disconnect() override {
		if (isConnected()) {
			asio::error_code ec;
			ssl_stream.shutdown(ec);
			if (!ec) 
				ConsoleLog::info("SSL shutdown completed");
			else
				ConsoleLog::error("Failed to shut down SSL: " + ec.message());

			ssl_stream.lowest_layer().close(ec);

			if (!ec)
				ConsoleLog::info("Succesfully disconnected");
			else
				ConsoleLog::error("Failed to disconnect: " + ec.message());

		}
	}
	bool isConnected() const override { return ssl_stream.lowest_layer().is_open(); }
	//listens for data
	virtual void listen() {
		asio::post(context, [this]() {
			reader->start(ssl_stream);
			});
	}
protected:
	void writeMessage(std::shared_ptr<messageTypeOut> msg) override {
		std::string str = msg->toString();
		//since asio handles chunking huge messages , I don't need to implement that.
		asio::async_write(ssl_stream, asio::buffer(str.data(), str.size()),
			[this , str](std::error_code ec, std::size_t length) {
				if (!ec) {
					writeQueue.pop_front();
					ConsoleLog::message("Sucessfully wrote a message");
					ConsoleLog::info("Request size: " + std::to_string(length));
					ConsoleLog::info(str);

					if(writeQueue.empty() == false)
						writeMessage(writeQueue.front());
				}
				else
					ConsoleLog::error("Failed to write a request to the server");
			});
	}
protected:
	asio::ssl::context& sslContext;
	SslSocket ssl_stream;

	//so apparently I need to let the compiler know about the member variables I use from it's parent class
	//otherwise it pisses itself
	using AbstractConnection<messageTypeIn, messageTypeOut , SslSocket>::context;
	using AbstractConnection<messageTypeIn, messageTypeOut , SslSocket>::writeQueue;
	using AbstractConnection<messageTypeIn, messageTypeOut, SslSocket>::reader;
};
