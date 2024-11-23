#include "HttpServerConnection.h"

HttpServerConnection::HttpServerConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<Message>>& queue)
	:Connection(context0, std::move(socket0), queue)
{}

void HttpServerConnection::listen() {
	initMsgReader();
	asio::post(context, [this]() {
		bool go = true;
		while (go)
		{
			go = reader->start(socket);
			if(go)
				readQueue.push_back();
		}
		//for error handling here maybe?

		});
}
void HttpServerConnection::initMsgReader() {
	reader = std::make_unique<HttpRequestReader>();
}