#pragma once
#include "HttpMessage.h"


class HttpResponse : public HttpMessage {
public:
	HttpResponse() = default;
	HttpResponse(const std::string& str, int32_t id = 0)
		:HttpMessage(str) 
	{
		setUserId(id);
	}
	HttpResponse(int32_t statusCode, const std::string& phrase,
		const HttpHeaders& headers, std::unique_ptr<rapidjson::Document> d0 = nullptr, int32_t id = 0)
		:HttpMessage(headers, std::move(d0)), _version(HttpCommon::VersionCodex::get().defaultVersion) , _statusCode(statusCode), _phrase(phrase)
	{
		setUserId(id);
	}

	HttpResponse(HttpCommon::Version version, int32_t statusCode, const std::string& phrase,
		const HttpHeaders& headers, std::unique_ptr<rapidjson::Document> d0 = nullptr , int32_t id = 0)
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
		if (doc != nullptr) {
			return responseFirstLine(_version, _statusCode, _phrase) +
				HttpHeaders::headersToString(_headers) +
				HttpMessage::documentToString(*doc);
		}
		else {
			return responseFirstLine(_version, _statusCode, _phrase) +
				HttpHeaders::headersToString(_headers);
		}
	}
	HttpCommon::Version version() const noexcept { return _version; }
	int32_t statusCode() const noexcept { return _statusCode; }
	std::string phrase() const noexcept { return _phrase; }
protected:
	void processFirstLine(const std::string& line) override {

	}
private:
	HttpCommon::Version _version;
	int32_t _statusCode;
	std::string _phrase;
};
