#pragma once
#include "rapidjson/document.h"
#include "MessageReader.h"
#include "Common.h"

class HttpReader : public MessageReader {
public:
	HttpReader();
	
	void start(asio::ip::tcp::socket& socket) override;
protected:
	virtual void processFirstLine(const std::vector<char>& buf) = 0;

	void readHeader(asio::ip::tcp::socket& socket);
	void readBody(asio::ip::tcp::socket& socket);
	void processHeaderLine(const std::vector<char>& buf);


private:
	bool jsonStarted() const;
private:
	std::map<ByteArray, ByteArray> headers;
	rapidjson::Document doc;
	std::array<std::string, 3> reqTypeStorage;

	ByteArray unfinishedMessage;
	ByteArray unfinishedLine;
	ByteArray buffer;

	//current line being processed. Don't want to realocate it all the time
	ByteArray line;

	int32_t jsonDocSize = 0;
	ByteArray jsonDocByteArr;


	int32_t bufferSize;
	bool firstLineRead = false;
};