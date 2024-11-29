#pragma once
#include "HttpMessage.h"


class HttpResponse : public HttpMessage {
public:
	HttpResponse(const std::string& str)
		:HttpMessage(str)
	{}
	HttpResponse(HttpCommon::Version version, int32_t statusCode, const std::string& phrase,
		const std::map<std::string, std::string>& headers, std::unique_ptr<rapidjson::Document> d0)
		:HttpMessage(headers, std::move(d0)), _version(version), _statusCode(statusCode), _phrase(phrase)
	{}

	static std::string responseFirstLine(HttpCommon::Version version, int32_t statusCode, const std::string& phrase) {
		return HttpCommon::VersionCodex::get().versionToString(version) + ' ' +
			std::to_string(statusCode) + ' ' + 
			phrase + '\n';
	}
	std::string toString() const override {
		return responseFirstLine(_version, _statusCode, _phrase) +
			HttpMessage::headersToString(_headers) +
			HttpMessage::documentToString(*doc);
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
