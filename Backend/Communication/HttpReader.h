#pragma once
#include "document.h"
#include "MessageReader.h"
#include "Common.h"
#include "HttpCommon.h"
#include "HttpRequest.h"

class HttpReader : public MessageReader {
public:
	HttpReader();
	
	bool start(asio::ip::tcp::socket& socket) override;
protected:
	virtual void processFirstLine(const std::vector<char>& buf) = 0;

	bool readHeader(asio::ip::tcp::socket& socket);
	bool readBody(asio::ip::tcp::socket& socket);
	void processHeaderLine(const std::vector<char>& buf);


private:
	bool jsonStarted() const;
protected:
	std::map<ByteArray, ByteArray> headers;
	std::unique_ptr<rapidjson::Document> doc;
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

class HttpRequestReader : public HttpReader{
public:
	HttpRequestReader() = default;
	ByteArray version() const noexcept;
	ByteArray URI() const noexcept;
	HttpVerb verb() const noexcept;

	std::unique_ptr<HttpRequest> request() const ;
protected:
	void processFirstLine(const std::vector<char>& buf) override;
protected:
	HttpVerb _verb;
	ByteArray _URI;
	ByteArray _version;

	bool ready = false;
};

class HttpResponseReader : public HttpReader {
public:
	HttpResponseReader() = default;
	ByteArray version() const noexcept;
	int16_t statusCode() const noexcept;
	ByteArray phrase() const noexcept;
protected:
	void processFirstLine(const std::vector<char>& buf) override;
protected:
	ByteArray _version;
	int16_t _statusCode;
	ByteArray _phrase;
};