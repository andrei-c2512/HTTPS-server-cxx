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
class RequestHeaders {
public:
	static RequestHeaders& get() {
		static RequestHeaders h;
		return h;
	}
	RequestHeaders& operator=(const RequestHeaders&) = delete;
	RequestHeaders(const RequestHeaders&) = delete;
	ByteArray headerString(HeaderType type) {
		return headers[int(type)];
	}
	HeaderType stringToType(const ByteArray& arr) {
		return headerMap[arr];
	}
private:
	RequestHeaders() {
		std::vector<std::string> vec = { "Content-type" , "Host" , "Content-Length" , "authorization" };
		for (const std::string& str : vec) {
			headers.emplace_back(ByteArray(vec.begin(), vec.end()));
		}

		if (headers.size() != int(HeaderType::COUNT))
			ConsoleLog::warning("Not all headers are implemented");

		for (auto i = 0; i < headers.size() ; i++) {
			headerMap.emplace(headers[i], HeaderType(i));
		}
	}
	std::map<ByteArray, HeaderType> headerMap;
	std::vector<ByteArray> headers;
};