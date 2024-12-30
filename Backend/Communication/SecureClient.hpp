#pragma once
#include "ClientInterface.hpp"
#include "Common.hpp"
#include "Message.hpp"
#include "TsQueue.hpp"
#include "ConsoleLog.hpp"

template<message messageTypeIn, message messageTypeOut, typename connectionType>
class SecureClient : public ClientInterface<messageTypeIn , messageTypeOut> {
public:
	SecureClient(const std::string& certificatePath , std::vector<std::string> approvedCerts)
		:sslContext(asio::ssl::context::sslv23) , workGuard(asioContext.get_executor())
	{
		contextThread = std::thread([this]() {
			asioContext.run();
		});

		asio::error_code ec;
		sslContext.use_certificate_chain_file(certificatePath, ec);
		_abort = _abort || ConsoleLog::handleError(ec, "Sucessfully loaded the certificate file", "Failed to use the certificate file");

		sslContext.set_verify_mode(asio::ssl::verify_peer);
		for (const std::string& filePath : approvedCerts) {
			sslContext.load_verify_file(filePath, ec);
			_abort = _abort || ConsoleLog::handleError(ec, "Added new file for verification", "Failed to load the certificate file");
		}
	}
	~SecureClient() {
		disconnect();
	}
	void connect(const std::string& host, int16_t port) {
		try {
			conn = std::make_shared<connectionType>(asioContext, sslContext , SslSocket(asioContext , sslContext), readQueue);
			conn->connect(host, port);
		}
		catch (std::exception& e) {
			ConsoleLog::error(e.what());
		}
	}
	void disconnect() {
		conn->disconnect();
		onDisconnect();
		asioContext.stop();

		if (contextThread.joinable()) contextThread.join();

		ConsoleLog::message("Disconnected from server");
	}
	bool isConnected() const noexcept { return conn->isConnected(); }

	void send(std::shared_ptr<messageTypeOut> msg) {
		assert(asioContext.stopped() == false);
		conn->send(msg);
	}
	void update() override {
		while (readQueue.empty() == false) {
			auto request = readQueue.front();
			readQueue.pop_front();
			ConsoleLog::info("Processing new message...");
			onNewMessage(request);
		}
	}
protected:
	using ClientInterface<messageTypeIn, messageTypeOut>::onDisconnect;
	using ClientInterface<messageTypeIn, messageTypeOut>::onNewMessage;
protected:
	asio::ssl::context sslContext;
	asio::io_context asioContext;
	asio::executor_work_guard<asio::io_context::executor_type> workGuard;
	std::thread contextThread;

	TsQueue<std::shared_ptr<messageTypeIn>> readQueue;

	std::shared_ptr<connectionType> conn;
	bool _abort = false;
};
