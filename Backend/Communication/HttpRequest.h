#pragma once
#include "rapidjson/document.h"
#include <string>
#include <map>
#include <array>
#include "Message.h"

class HttpRequest : public Message{
public:
	HttpRequest(const std::string& str);

	std::string method() const noexcept;
	std::string url() const noexcept;
	std::string scheme() const noexcept;
	std::string server() const noexcept;
	std::string path() const noexcept;
	std::string version() const noexcept;
private:
	void extractMethod();
	void extractUrl();
	void extractScheme();
	void extractServer();
	void extractPath();
	int32_t extractHeaders(const std::string& str, int32_t start);
private:
	std::map<std::string, std::string> headers;
	rapidjson::Document d;
	std::array<std::string, 3> reqTypeStorage;
};