#pragma once
#include "ConsoleLog.h"
#include "document.h"
#include "Common.h"
#include "StringHelper.h"
#include "writer.h"
#include "stringbuffer.h"

enum class HeaderType {
	CONTENT_TYPE,
	HOST,
	CONTENT_LENGTH,
	AUTHORIZATION,
	COUNT
};

enum class HttpVerb {
	GET,
	HEAD,
	POST,
	PUT,
	//added _ cause there is a macro called DELETE , bruh
	_DELETE,
	UPDATE,
	CONNECT,
	OPTIONS,
	TRACE
};

enum class HttpVersion {
	HTTP09,
	HTTP10,
	HTTP11
};

//HttpCommon::HttpVersion::blablabla

class HttpCommon {
public:
	HttpCommon& operator=(const HttpCommon&) = delete;
	HttpCommon(const HttpCommon&) = delete;

	static std::string headersToString(const std::map<ByteArray, ByteArray>& headers) {
		std::string headerText;

		for (const auto& [key, value] : headers) {
			std::string line;
			line.append(key.begin(), key.end());
			line.append(":");
			line.append(value.begin(), value.end());
			line.append("\n");

			headerText.append(line);
		}

		return headerText;
	}
	static ByteArray headersToByteArray(const std::map<ByteArray, ByteArray>& headers) {
		ByteArray headerText;
		ByteArray sep1;
		sep1.emplace_back(':');

		ByteArray sep2;
		sep2.emplace_back('\n');

		
		for (const auto& [key, value] : headers) {
			ByteArray line;

			//refactor
			StringHelper::appendToByteArray(line, key);
			StringHelper::appendToByteArray(line, sep1);
			StringHelper::appendToByteArray(line, value);
			StringHelper::appendToByteArray(line, sep2);
			////////

			//read
			// listen pt bytes => procesare
			//write
			// dau build la un fel de mesaj => bytes

			StringHelper::appendToByteArray(headerText, line);
		}

		return headerText;
	}
	static std::string documentToString(const rapidjson::Document& doc) {
		rapidjson::StringBuffer buf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
		doc.Accept(writer);

		return std::string(buf.GetString());
		return std::string();
	}
	static ByteArray documentToByteArray(const rapidjson::Document& doc) {
		std::string str = documentToString(doc);

		return ByteArray(str.begin(), str.end());
	}

	ByteArray headerString(HeaderType type) {
		return headers[int(type)];
	}
	HeaderType stringToHeaderType(const ByteArray& arr) {
		return headerMap[arr];
	}
	ByteArray verbToString(HttpVerb verb) {
		return verbs[int(verb)];
	}
	HttpVerb stringToVerb(const ByteArray& arr) {
		return verbMap[arr];
	}
	ByteArray versionToString(HttpVersion version) {
		return versions[int(version)];
	}
	HttpVersion stringToVersion(const ByteArray& arr) {
		return versionMap[arr];
	}

	static HttpCommon& get() {
		static HttpCommon h;
		return h;
	}
private:
	HttpCommon() {
		std::vector<std::string> headerVec = { "Content-type" , "Host" , "Content-Length" , "authorization" };
		headers = StringHelper::toByteArrayVec(std::move(headerVec));

		if (headers.size() != int(HeaderType::COUNT))
			ConsoleLog::warning("Not all headers are implemented");

		for (auto i = 0; i < headers.size(); i++) {
			headerMap.emplace(headers[i], HeaderType(i));
		}

		std::vector<std::string> verbVec = { "GET" , "HEAD" , "POST" , "PUT" , "DELETE" , "UPDATE" , "CONNECT" , "OPTIONS" , "TRACE" };
		verbs = StringHelper::toByteArrayVec(std::move(verbVec));

		for (auto i = 0; i < verbs.size(); i++) {
			verbMap.emplace(verbs[i], HttpVerb(i));
		}

		std::vector<std::string> versionVec = { "HTTP/0.9" , "HTTP/1.0" , "HTTP/1.1" };
		versions = StringHelper::toByteArrayVec(std::move(versionVec));

		for (auto i = 0; i < versions.size(); i++) {
			versionMap.emplace(versions[i], HttpVersion(i));
		}
	}
	std::map<ByteArray, HeaderType> headerMap;
	std::vector<ByteArray> headers;

	std::map<ByteArray, HttpVerb> verbMap;
	std::vector<ByteArray> verbs;

	std::map<ByteArray, HttpVersion> versionMap;
	std::vector<ByteArray> versions;
};
