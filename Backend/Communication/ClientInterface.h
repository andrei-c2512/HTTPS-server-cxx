#pragma once
#include <string>
#include <memory>

template <typename messageTypeOut>
class ClientInterface {
public:
	virtual void connect(const std::string& host, int16_t port) = 0;
	virtual void disconnect() = 0;
	virtual bool isConnected() const = 0;
	virtual void send(std::shared_ptr<messageTypeOut> msg) = 0;
};