#pragma once
#pragma once
#include "TsQueue.h"
#include "Message.h"
#include "ConsoleLog.h"
#include "MessageReader.h"

template<message messageTypeIn, message messageTypeOut , IsSocket socketType>
class AbstractConnection {
public:
	AbstractConnection(asio::io_context& context0,
		TsQueue<std::shared_ptr<messageTypeIn>>& queue)
		:context(context0), readQueue(queue)
	{
		//subclasses should instantiate their reader here
		// I do not want the reader to be set from the constructor , I think it's ugly design in this case
		// unlesss you want some custom reader , which I should add the setting for(because , well , there will be encrypted
		// readings and perhaps you want anything other than the default encryption)
	}
	//deleting cause I don't see the use
	AbstractConnection& operator=(const AbstractConnection&) = delete;
	AbstractConnection(const AbstractConnection&) = delete;
	virtual ~AbstractConnection() {
		disconnect();
		if (reader) {
			delete reader;
			reader = nullptr;
		}
	}
public:
	virtual bool connect(const std::string& host, int16_t port) { return false; }
	virtual void disconnect() {}
	virtual bool isConnected() const { return false; }
	virtual void setId(int32_t id0) noexcept { 
		_id = id0; 
		if (reader != nullptr)
			reader->setUserId(id0);
	}

	int32_t id() const noexcept { return _id; }
	//listens for data
	virtual void listen(){}
public:
	void send(std::shared_ptr<messageTypeOut> msg) {
		asio::post(context, [this, msg]() {
			//ConsoleLog::info("Attempting to post");
			bool isWriting = !writeQueue.empty();
			writeQueue.push_back(msg);
			if (!isWriting) {
				writeMessage(msg);
			}
			});
	}
protected:
	virtual void writeMessage(std::shared_ptr<messageTypeOut> msg) = 0;
protected:
	asio::io_context& context;
	TsQueue<std::shared_ptr<messageTypeOut>> writeQueue;
	TsQueue<std::shared_ptr<messageTypeIn>>& readQueue;

	int32_t _id = -1;

	AbstractMessageReader<socketType>* reader = nullptr;
};


template <typename T, typename mIn, typename mOut , typename socket>
concept connection =
message<mIn> &&
message<mOut> &&
IsSocket<socket> &&
std::is_base_of_v<AbstractConnection<mIn, mOut , socket>, T>;
