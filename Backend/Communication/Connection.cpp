#include "Connection.h"
#include "ConsoleLog.h"

Connection::Connection(asio::io_context& context0, 
	asio::ip::tcp::socket socket0 , 
	TsQueue<std::shared_ptr<Message>>& queue ,
	Connection::Type type0)
	:context(context0) , socket(std::move(socket0)) , readQueue(queue) ,type(type0)
{

}

Connection::~Connection() {
	delete messageReader;
}

bool Connection::connect(const std::string& host, int16_t port) {
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
	catch(std::exception& e){
		ConsoleLog::error(e.what());

	}
}

void Connection::initMsgReader() {
	switch (type) {
	case Type::TCP:
		break;
	case Type::Http:
		break;
	case Type::Https:
		break;
	}
}

//listens for data
void Connection::listen() {
	messageReader->start(socket);
}

bool Connection::disconnect() {
	return false;
}
bool Connection::isConnected() const {
	return false;
}
void Connection::write(std::shared_ptr<Message> msg) {

}

void Connection::setId(int32_t id0) {
	_id = id0;
}

int32_t Connection::id() const noexcept { return _id;  }