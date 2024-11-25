#pragma once
#include "HttpMessage.h"


class HttpResponse : public HttpMessage {
public:
	HttpResponse(const std::string& str);
	HttpResponse(HttpVersion version, int32_t statusCode, const ByteArray& phrase,
		const std::map<ByteArray, ByteArray>& headers, std::unique_ptr<rapidjson::Document> d0)
		:HttpMessage(headers, std::move(d0)), _version(version), _statusCode(statusCode), _phrase(phrase)
	{}

	HttpVersion version() const noexcept { return _version; }
	int32_t statusCode() const noexcept { return _statusCode; }
	ByteArray phrase() const noexcept { return _phrase; }
protected:
	void processFirstLine(const std::string& line) override {

	}
private:
	HttpVersion _version;
	int32_t _statusCode;
	ByteArray _phrase;
};
