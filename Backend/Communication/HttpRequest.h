#pragma once
#include "HttpMessage.h"


class HttpRequest : public HttpMessage {
public:
	HttpRequest() = default;
	HttpRequest(const std::string& str , int32_t id = 0)
		:HttpMessage(str) 
	{
		setUserId(id);
		/*int32_t i = 0;
		int32_t strCursor = 0;
		int32_t last = 0;

		char breakChar = ' ';
		for (; strCursor < str.size(); strCursor++) {
			if (str[strCursor] == breakChar)
			{
				reqTypeStorage[i] = str.substr(last, i - last);
				last = i + 1;
				i++;
				if (i == 2)
					breakChar = '\n';
				else if (i == 3)
					break;
			}
		}
		extractHeaders(str, strCursor);*/
	}
	HttpRequest(HttpCommon::Verb v, const std::string& URI0,
		const HttpHeaders& headers0, std::unique_ptr<rapidjson::Document> d0, int32_t id = 0)
		:HttpMessage(headers0, std::move(d0)), _verb(v), _URI(URI0), _version(HttpCommon::VersionCodex::get().defaultVersion)
	{
		setUserId(id);
	}
	HttpRequest(HttpCommon::Verb v, const std::string& URI0, HttpCommon::Version version0,
		const HttpHeaders& headers0, std::unique_ptr<rapidjson::Document> d0 , int32_t id = 0)
		:HttpMessage(headers0, std::move(d0)), _verb(v), _URI(URI0), _version(version0)
	{
		setUserId(id);
	}

	static std::string requestFirstLine(HttpCommon::Verb verb , const std::string& URI  , HttpCommon::Version version) {
		return HttpCommon::VerbCodex::get().verbToString(verb) + ' ' + 
			URI + ' ' + 
			HttpCommon::VersionCodex::get().versionToString(version) + '\n';
	}
	HttpCommon::Verb verb() const noexcept { return _verb; }
	std::string URI() const noexcept { return _URI; }
	HttpCommon::Version version() const noexcept { return _version; }
	
	//might implement later lol
	std::string scheme() const noexcept;
	std::string server() const noexcept;
	std::string path() const noexcept;

	std::string toString() const override {
		if (doc != nullptr) {
			return requestFirstLine(_verb, _URI, _version) +
				HttpHeaders::headersToString(_headers) +
				HttpMessage::documentToString(*doc);
		}
		else {
			return requestFirstLine(_verb, _URI, _version) +
				HttpHeaders::headersToString(_headers);
		}
	}
protected:
	void processFirstLine(const std::string& line) override {

	}
private:
	void extractMethod();
	void extractUrl();
	void extractScheme();
	void extractServer();
	void extractPath();
	int32_t extractHeaders(const std::string& str, int32_t start);
private:
	HttpCommon::Verb _verb;
	std::string _URI;
	HttpCommon::Version _version;
};

