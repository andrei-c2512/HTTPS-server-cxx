#pragma once
#include "Common.h"
#include "ConsoleLog.h"

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

class HttpCommon {
public:
	static HttpCommon& get();
	HttpCommon& operator=(const HttpCommon&) = delete;
	HttpCommon(const HttpCommon&) = delete;
	ByteArray headerString(HeaderType type);
	HeaderType stringToHeaderType(const ByteArray& arr);

	ByteArray verbString(HttpVerb verb);
	HttpVerb stringToVerb(const ByteArray& arr);
private:
	HttpCommon();
	std::map<ByteArray, HeaderType> headerMap;
	std::vector<ByteArray> headers;

	std::map<ByteArray, HttpVerb> verbMap;
	std::vector<ByteArray> verbs;
};