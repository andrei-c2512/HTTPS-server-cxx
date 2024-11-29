#pragma once
#include "TsQueue.h"
#include "Message.h"
#include "ConsoleLog.h"


template<message messageTypeIn , message messageTypeOut>
class Connection {
public:
	Connection(asio::io_context& context0,
		asio::ip::tcp::socket socket0,
		TsQueue<std::shared_ptr<messageTypeIn>>& queue)
		:context(context0), socket(std::move(socket0)), readQueue(queue)
	{}
	Connection& operator=(const Connection&) = delete;
	Connection(const Connection&) = delete;

	virtual ~Connection() {
		disconnect();
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
				});
			return true;
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());
			return false;
		}
	}
	void disconnect() { 
		if (isConnected())
			asio::post(context, [this]() {
			ConsoleLog::message("Disconnecting from the server");
			socket.close();
				});
	}
	bool isConnected() const { return socket.is_open(); }
	void setId(int32_t id0) { _id = id0; }

	int32_t id() const noexcept { return _id; }
	//listens for data
	virtual void listen() = 0;
	virtual void writeMessage(std::shared_ptr<messageTypeOut> msg) = 0;
public:
	void send(std::shared_ptr<messageTypeOut> msg) {
		asio::post(context, [this , msg]() {
			//ConsoleLog::info("Attempting to post");
			bool isWriting = !writeQueue.empty();
			writeQueue.push_back(msg);
			if (!isWriting) {
				writeMessage(msg);
			}
		});
	}
protected:
	asio::ip::tcp::socket socket;
	asio::io_context& context;
	TsQueue<std::shared_ptr<messageTypeOut>> writeQueue;
	TsQueue<std::shared_ptr<messageTypeIn>>& readQueue;

	int32_t _id = -1;
};


template <typename T, typename mIn, typename mOut>
concept connection =
			message<mIn> &&                     
			message<mOut> &&                    
			std::is_base_of_v<Connection<mIn, mOut>, T>;
