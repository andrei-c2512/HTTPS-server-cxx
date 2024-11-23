#include "HttpRequest.h"
#include "StringHelper.h"

HttpRequest::HttpRequest(const std::string& str) {
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

HttpRequest::HttpRequest(HttpVerb v, const ByteArray& URI0, const ByteArray& version0,
	const std::map<ByteArray, ByteArray>& headers0, std::unique_ptr<rapidjson::Document> d0)
	:_verb(v) , _URI(URI0) , _version(version0) , headers(headers0) , doc(std::move(d0))
{}


/*int32_t HttpRequest::extractHeaders(const std::string& str, int32_t start) {
	char ch = str[start];
	char startOfJson = '{';

	while (ch != startOfJson) {
		//i would use std::istringstream to read line by line but I don't want to make a copy of the string
		std::string line = StringHelper::nextLine(str, start);
	}

	return start;
}
*/

HttpVerb HttpRequest::verb() const noexcept { return _verb; }
ByteArray HttpRequest::URI() const noexcept { return _URI; }
ByteArray HttpRequest::version() const noexcept { return _version; };
const rapidjson::Document& HttpRequest::document() const noexcept { return *doc; }

//std::string HttpRequest::method() const noexcept { return reqTypeStorage[0]; }
//std::string HttpRequest::scheme() const noexcept { return ""; }
//std::string HttpRequest::server() const noexcept { return ""; }
//std::string HttpRequest::path() const noexcept { return ""; }
