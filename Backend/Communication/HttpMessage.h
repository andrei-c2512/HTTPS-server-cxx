#pragma once
#include "Message.h"
#include "HttpCommon.h"
#include "StringHelper.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "prettywriter.h"
#include "HttpHeaders.h"


class HttpMessage : public Message {
public:
	HttpMessage() = default;
	HttpMessage(const std::string& str)
	{
		int32_t i = 0;
		std::string firstLine = StringHelper::nextLine(str, i);
		processFirstLine(firstLine);
		processHeaders(str, i);
		processBody(str, i);
	}
	HttpMessage(const HttpHeaders& headers0, std::unique_ptr<rapidjson::Document> d0)
		:_headers(headers0), doc(std::move(d0))
	{}
	const rapidjson::Document& document() const noexcept { return *doc; }
	HttpHeaders headers() const noexcept { return _headers; }
	static std::string documentToString(const rapidjson::Document& doc) {
		rapidjson::StringBuffer buf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
		doc.Accept(writer);

		return buf.GetString();
	}
	static std::string documentToPrettyString(const rapidjson::Document& doc) {
		rapidjson::StringBuffer buf;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
		doc.Accept(writer);

		return buf.GetString();
	}
protected:
	virtual void processFirstLine(const std::string& line) = 0;
	void processHeaders(const std::string& str, int32_t& pos) {

	}
	void processBody(const std::string& str, int32_t& pos) {

	}
protected:
	HttpHeaders _headers;
	std::unique_ptr<rapidjson::Document> doc = nullptr;
};

