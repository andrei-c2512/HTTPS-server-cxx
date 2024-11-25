#pragma once
#include "TsQueue.h"
#include "Message.h"
#include "ConsoleLog.h"


template<message messageType>
class Connection {
public:
	Connection(asio::io_context& context0,
		asio::ip::tcp::socket socket0,
		TsQueue<std::shared_ptr<messageType>>& queue)
		:context(context0), socket(std::move(socket0)), readQueue(queue)
	{}
	Connection& operator=(const Connection&) = delete;
	Connection(const Connection&) = delete;
public:
	bool connect(const std::string& host, int16_t port) {
		try {
			asio::ip::tcp::resolver resolver(context);
			asio::ip::tcp::resolver::results_type endpoint = resolver.resolve(host, std::to_string(port));

			asio::async_connect(socket, endpoint,
				[this](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
					if (!ec) {
						listen();
					}
				});
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());

		}
	}
	bool disconnect() { return false; }
	bool isConnected() const { return socket.is_open(); }
	void setId(int32_t id0) { _id = id0; }

	int32_t id() const noexcept { return _id; }
	//listens for data
	virtual void listen() = 0;
	virtual void writeMessage(std::shared_ptr<messageType> msg) = 0;
public:
	void send(std::shared_ptr<messageType> msg) {
		asio::post(context, []() {
			bool isWriting = !writeQueue.empty();
			if (!isWriting) {
				writeMessage(msg);
			}
			});
	}
protected:
	asio::ip::tcp::socket socket;
	asio::io_context& context;
	TsQueue<std::shared_ptr<messageType>> writeQueue;
	TsQueue<std::shared_ptr<messageType>>& readQueue;

	int32_t _id = -1;
};


template <typename T, typename M>
concept connection = std::is_base_of_v<Connection<M> , T>;
