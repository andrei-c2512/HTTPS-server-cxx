#include "HttpCommon.h"
#include "StringHelper.h"

HttpCommon::HttpCommon() {
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
}

ByteArray HttpCommon::headerString(HeaderType type) {
	return headers[int(type)];
}
HeaderType HttpCommon::stringToHeaderType(const ByteArray& arr) {
	return headerMap[arr];
}

ByteArray HttpCommon::verbString(HttpVerb verb) {
	return verbs[int(verb)];
}

HttpVerb HttpCommon::stringToVerb(const ByteArray& arr) {
	return verbMap[arr];
}

HttpCommon& HttpCommon::get() {
	static HttpCommon h;
	return h;
}