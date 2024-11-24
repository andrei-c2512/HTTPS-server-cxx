#pragma once
#include "Message.h"
#include "Common.h"
#include "HttpCommon.h"
#include "document.h"

class HttpRequest : public Message{
public:
	HttpRequest(const std::string& str);
	HttpRequest(HttpVerb v, const ByteArray& URI0, const ByteArray& version0, 
		const std::map<ByteArray,ByteArray>& headers, std::unique_ptr<rapidjson::Document> d0);


	HttpVerb verb() const noexcept;
	ByteArray URI() const noexcept;
	/*
	std::string scheme() const noexcept;
	std::string server() const noexcept;
	std::string path() const noexcept;*/
	ByteArray version() const noexcept;
	const rapidjson::Document& document() const noexcept;
private:
	/*void extractMethod();
	void extractUrl();
	void extractScheme();
	void extractServer();
	void extractPath();
	int32_t extractHeaders(const std::string& str, int32_t start);*/
private:
	HttpVerb _verb;
	ByteArray _URI;
	ByteArray _version;
	std::map<ByteArray, ByteArray> headers;
	std::unique_ptr<rapidjson::Document> doc;
};