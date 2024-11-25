#pragma once
#include "Message.h"
#include "HttpCommon.h"
#include "StringHelper.h"



class HttpMessage : public Message {
public:
	HttpMessage(const std::string& str)
	{
		int32_t i = 0;
		std::string firstLine = StringHelper::nextLine(str, i);
		processFirstLine(firstLine);
		processHeaders(str, i);
		processBody(str, i);
	}
	HttpMessage(const std::map<ByteArray, ByteArray>& headers0, std::unique_ptr<rapidjson::Document> d0)
		:_headers(headers0), doc(std::move(d0))
	{}
	const rapidjson::Document& document() const noexcept { return *doc; }
	std::map<ByteArray, ByteArray> headers() const noexcept { return _headers; }
protected:
	virtual void processFirstLine(const std::string& line) = 0;
	void processHeaders(const std::string& str, int32_t& pos) {

	}
	void processBody(const std::string& str, int32_t& pos) {

	}
protected:
	std::map<ByteArray, ByteArray> _headers;
	std::unique_ptr<rapidjson::Document> doc;
};

