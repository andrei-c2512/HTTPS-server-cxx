#pragma once
#include "Message.hpp"
#include "HttpCommon.hpp"
#include "StringHelper.hpp"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "prettywriter.h"
#include "HttpHeaders.hpp"


class HttpMessage : public Message {
public:
	HttpMessage() = default;
	HttpMessage(const std::string& str)
	{
		doc.SetObject();
		int32_t i = 0;
		std::string firstLine = StringHelper::nextLine(str, i);
		processFirstLine(firstLine);
		processHeaders(str, i);
		processBody(str, i);
	}
	HttpMessage(const HttpHeaders& headers0, rapidjson::Document d0)
		:_headers(headers0), doc(std::move(d0))
	{}
	const rapidjson::Document& document() const noexcept { return doc; }
	const HttpHeaders& headers() const noexcept { return _headers; }
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
	rapidjson::Document doc;
};

