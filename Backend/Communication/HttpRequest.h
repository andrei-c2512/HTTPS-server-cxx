#pragma once
#include "HttpMessage.h"


class HttpRequest : public HttpMessage {
public:
	HttpRequest(const std::string& str)
		:HttpMessage(str)
	{
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
	HttpRequest(HttpVerb v, const ByteArray& URI0, HttpVersion version0,
		const std::map<ByteArray, ByteArray>& headers0, std::unique_ptr<rapidjson::Document> d0)
		:HttpMessage(headers0, std::move(d0)), _verb(v), _URI(URI0), _version(version0)
	{}


	HttpVerb verb() const noexcept { return _verb; }
	ByteArray URI() const noexcept { return _URI; }
	HttpVersion version() const noexcept { return _version; }
	
	std::string scheme() const noexcept;
	std::string server() const noexcept;
	std::string path() const noexcept;
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
	HttpVerb _verb;
	ByteArray _URI;
	HttpVersion _version;
};

