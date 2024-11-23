#pragma once
#include "Connection.h"


//if you are a client and want to connect to a server , use this
//this one is is ready to read incoming responses(since clients only need to read responses)
class HttpClientConnection : public Connection {
public:
	HttpClientConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<Message>>& queue);
	void listen() override;
protected:
	void initMsgReader() override;
protected:
	std::unique_ptr<MessageReader> reader;
};