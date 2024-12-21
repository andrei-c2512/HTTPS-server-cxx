#pragma once
#include "ClientInterface.h"
#include "Common.h"
#include "Message.h"
#include "TsQueue.h"
#include "ConsoleLog.h"

template<message messageTypeIn, message messageTypeOut, typename connectionType>
class SecureClient : public ClientInterface<messageTypeOut> {
public:
	SecureClient(const std::string& certificatePath , std::vector<std::string> approvedCerts)
		:sslContext(asio::ssl::context::sslv23)
	{
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

			asio::executor_work_guard<asio::io_context::executor_type> work_guard(asioContext.get_executor());

			contextThread = std::thread([this]() {
				asioContext.run();
			});
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
		conn->send(msg);
	}
protected:
	virtual void onDisconnect() {}
protected:
	asio::ssl::context sslContext;
	asio::io_context asioContext;
	std::thread contextThread;

	TsQueue<std::shared_ptr<messageTypeIn>> readQueue;

	std::shared_ptr<connectionType> conn;
	bool _abort = false;
};
