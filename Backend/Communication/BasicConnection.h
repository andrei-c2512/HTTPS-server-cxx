#pragma once
#include "AbstractConnection.h"
#include "Common.h"

template<message messageTypeIn , message messageTypeOut>
class BasicConnection : public AbstractConnection<messageTypeIn , messageTypeOut , BasicSocket> {
public:
	BasicConnection(asio::io_context& context0,
		BasicSocket socket0,
		TsQueue<std::shared_ptr<messageTypeIn>>& queue0)
		:AbstractConnection<messageTypeIn , messageTypeOut , BasicSocket>(context0 , queue0) ,
		socket(std::move(socket0))
	{
		//subclasses should instantiate their reader here
		// I do not want the reader to be set from the constructor , I think it's ugly design in this case
		// unlesss you want some custom reader , which I should add the setting for(because , well , there will be encrypted
		// readings and perhaps you want anything other than the default encryption)
	}
	//deleting cause I don't see the use
	BasicConnection& operator=(const BasicConnection&) = delete;
	BasicConnection(const BasicConnection&) = delete;
	virtual ~BasicConnection() {
	}
public:
	bool connect(const std::string& host, int16_t port) {
		try {
			asio::ip::tcp::resolver resolver(context);
			asio::ip::tcp::resolver::results_type endpoint = resolver.resolve(host, std::to_string(port));

			asio::async_connect(socket, endpoint,
				[this, host , port](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
					if (!ec) {
						ConsoleLog::message("Sucessfully connected to " + host + ":" + std::to_string(port));
						listen();
					}
					else {
						ConsoleLog::warning("Failed to connect to server, trying again...");
						connect(host, port);
					}
				});
			return true;
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());
			return false;
		}
	}
	void disconnect() override{ 
		if (isConnected())
			asio::post(context, [this]() {
			ConsoleLog::message("Disconnecting from the server");
			socket.cancel();
			socket.close();
		});
	}
	bool isConnected() const override { return socket.is_open(); }
	//listens for data
	virtual void listen() {
		reader->start(socket);
	}
protected:
	void writeMessage(std::shared_ptr<messageTypeOut> msg) override {
		std::string str = msg->toString();
		//since asio handles chunking huge messages , I don't need to implement that.
		asio::async_write(socket, asio::buffer(str.data(), str.size()),
			[this](std::error_code ec, std::size_t length) {
				if (!ec) {
					writeQueue.pop_front();
					ConsoleLog::info("Sucessfully wrote a request to the server");
					ConsoleLog::info("Request size: " + std::to_string(length));

					if(writeQueue.empty() == false)
						writeMessage(writeQueue.front());
				}
				else
					ConsoleLog::error("Failed to write a request to the server");
			});
	}
protected:
	BasicSocket socket;

	//so apparently I need to let the compiler know about the member variables I use from it's parent class
	//otherwise it pisses itself
	using AbstractConnection<messageTypeIn, messageTypeOut, BasicSocket>::context;
	using AbstractConnection<messageTypeIn, messageTypeOut, BasicSocket>::writeQueue;
	using AbstractConnection<messageTypeIn, messageTypeOut, BasicSocket>::reader;
};

