#pragma once
#include "HttpClient.h"
#include <memory>
#include <fstream>
#include "HttpRequest.h"
#include "HttpHeader.h"


class Client : public HttpClient{
public:
	Client() {
		connect("127.0.0.1", 3756);
	}
	void sendTestMessage(const std::string_view& fileName) {
		std::ifstream fin(fileName.data());

		std::string docStr;
		std::string aux;

		while (fin >> aux) {
			docStr += aux;
		}

		std::unique_ptr<rapidjson::Document> doc = std::make_unique<rapidjson::Document>();
		if (doc->Parse(docStr.c_str()).HasParseError()) {
			ConsoleLog::error("Parsing error in Client.h");
		}
		//ConsoleLog::info(HttpMessage::documentToPrettyString(*doc));


		HttpHeader header;
		header.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(docStr.size()));
		header.add(HttpCommon::Header::CONTENT_TYPE, "json");
		
		std::shared_ptr<HttpRequest> req = std::make_shared<HttpRequest>(
			HttpCommon::Verb::POST, "/login",
			HttpCommon::Version::HTTP11, header.map(), std::move(doc)
		);
		ConsoleLog::info(req->toString());

		send(req);
	}
};