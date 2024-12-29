#pragma once
#include "HttpClient.h"
#include <memory>
#include <fstream>
#include "HttpRequest.h"
#include "HttpHeaders.h"
#include "HttpsClient.h"


class Client : public HttpsClient{
public:
	Client()
	:HttpsClient("C:/Users/Andrei C/security/ca.crt" , std::vector<std::string>(1, "C:/Users/Andrei C/security/ca.crt")){
		connect("127.0.0.1", 3756);
	}
	void sendTestMessage(const std::string_view& fileName) {
		/*std::ifstream fin(fileName.data());

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


		HttpHeaders header;
		header.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(docStr.size()));
		header.add(HttpCommon::Header::CONTENT_TYPE, "json");
		
		std::shared_ptr<HttpRequest> req = std::make_shared<HttpRequest>(
			HttpCommon::Verb::POST, "/",
			HttpCommon::Version::HTTP11, header, std::move(doc)
		);
		ConsoleLog::info(req->toString());

		send(req);*/
	}
	void registerTest() {
		rapidjson::Document doc;
		doc.SetObject();
		//ConsoleLog::info(HttpMessage::documentToPrettyString(*doc));
		doc.AddMember("name", "Apetrei", doc.GetAllocator());
		doc.AddMember("email", "cykablyat@gmail.com", doc.GetAllocator());
		doc.AddMember("password", "12345678", doc.GetAllocator());

		rapidjson::StringBuffer buf;
		rapidjson::Writer writer(buf);
		doc.Accept(writer);

		HttpHeaders header;
		header.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(buf.GetSize()));
		header.add(HttpCommon::Header::CONTENT_TYPE, "json");

		std::shared_ptr<HttpRequest> req = std::make_shared<HttpRequest>(
			HttpCommon::Verb::POST, "/register",
			HttpCommon::Version::HTTP11, header, std::move(doc)
		);
		ConsoleLog::info(req->toString());

		send(req);
	}
protected:
	//void onNewMessage(std::shared_ptr<HttpRequest> req) override {

	//}
};
