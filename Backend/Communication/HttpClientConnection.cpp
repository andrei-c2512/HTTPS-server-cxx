#include "HttpClientConnection.h"

HttpClientConnection::HttpClientConnection(asio::io_context& context0, asio::ip::tcp::socket socket0, TsQueue<std::shared_ptr<Message>>& queue)
	:Connection(context0, std::move(socket0), queue)
{}

void HttpClientConnection::listen() {
	initMsgReader();
	asio::post(context, [this]() {
		bool go = true;
		while (go)
		{
			go = reader->start(socket);
		}
		//for error handling here maybe?

		});
}
void HttpClientConnection::initMsgReader() {
	reader = std::make_unique<HttpResponseReader>();
}