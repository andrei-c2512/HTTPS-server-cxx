#pragma once
#include <vector>
#include <string>

enum class HeaderType {
	CONTENT_TYPE,
	HOST,
	CONTENT_LENGTH,
	AUTHORIZATION,
	COUNT
};
class RequestHeaders {
public:
	RequestHeaders& get() {
		static RequestHeaders headers;
		return headers;
	}
	RequestHeaders& operator=(const RequestHeaders&) = delete;
	RequestHeaders(const RequestHeaders&) = delete;
	std::string headerString(HeaderType type) {
		return headers[int(type)];
	}
private:
	RequestHeaders() {
		headers = { "Content-type" , "Host" , "Content-length" , "authorization" };
	}
	std::vector<std::string> headers;
};