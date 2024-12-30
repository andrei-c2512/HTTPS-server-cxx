#pragma once
#include "HttpMessage.hpp"


class HttpResponse : public HttpMessage {
public:
	HttpResponse() = default;
	HttpResponse(const std::string& str, int32_t id = 0)
		:HttpMessage(str) 
	{
		setUserId(id);
	}
	HttpResponse(int32_t statusCode, const std::string& phrase,
		const HttpHeaders& headers, rapidjson::Document d0 = {}, int32_t id = 0)
		:HttpMessage(headers, std::move(d0)), _version(HttpCommon::VersionCodex::get().defaultVersion) , _statusCode(statusCode), _phrase(phrase)
	{
		setUserId(id);
	}

	HttpResponse(HttpCommon::Version version, int32_t statusCode, const std::string& phrase,
		const HttpHeaders& headers, rapidjson::Document d0 = {} ,  int32_t id = 0)
		:HttpMessage(headers, std::move(d0)), _version(version), _statusCode(statusCode), _phrase(phrase)
	{
		setUserId(id);
	}

	static std::string responseFirstLine(HttpCommon::Version version, int32_t statusCode, const std::string& phrase) {
		return HttpCommon::VersionCodex::get().versionToString(version) + ' ' +
			std::to_string(statusCode) + ' ' + 
			phrase + '\n';
	}
	std::string toString() const override {
		if (doc.MemberCount() != 0) {
			return responseFirstLine(_version, _statusCode, _phrase) +
				HttpHeaders::headersToString(_headers) +
				HttpMessage::documentToString(doc);
		}
		else {
			return responseFirstLine(_version, _statusCode, _phrase) +
				HttpHeaders::headersToString(_headers);
		}
	}
	HttpCommon::Version version() const noexcept { return _version; }
	int32_t statusCode() const noexcept { return _statusCode; }
	std::string phrase() const noexcept { return _phrase; }

	static std::unique_ptr<HttpResponse> createErrorResponse(const std::string_view& error) {
		rapidjson::Document body;
		body.SetObject();
		rapidjson::Value errorValue(error.data(), body.GetAllocator());

		body.AddMember("error", errorValue, body.GetAllocator());
		HttpHeaders headers;
		headers.add(HttpCommon::Header::CONTENT_TYPE, "application/json");
		headers.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(StringHelper::jsonCharLength(body)));

		return std::make_unique<HttpResponse>(400 ,  "Bad request", std::move(headers), std::move(body));
	}
protected:
	void processFirstLine(const std::string& line) override {

	}
private:
	HttpCommon::Version _version;
	int32_t _statusCode;
	std::string _phrase;
};
