#define _CRT_SECURE_NO_DEPRECATE
#include "Server.h"
#include <cstdlib>
const std::string host = "localhost";
const int16_t     dbPort = 5432;
const std::string dbName = "driveapp";
const std::string user = "authserver";
const std::string password = std::getenv("STREAMING_APP_DB");


Server::Server(int32_t port)
	:HttpsServer(port,
		"C:/Users/Andrei C/security/ca.crt",
		"C:/Users/Andrei C/security/ca.key", std::vector<std::string>(1, "C:/Users/Andrei C/security/ca.crt")),
	dbHandler(host, dbPort, dbName, user, password),
	jwtGenerator("C:/Users/Andrei C/security/jwt_private_key.pem"),
	jwtVerifier("C:/Users/Andrei C/security/jwt_public_key.pem")
{
	initRouter();
}

bool Server::assignFieldValue(const char** dest, const rapidjson::Document& body, const char* field) {
	if (body.HasMember(field) && body[field].IsString()) {
		*dest = body[field].GetString();
		return true;
	}
	else
		return false;
}


void Server::initRouter() {
	auto router = std::make_unique<ListRouter>();
	router->addRoute(HttpCommon::Verb::GET , "/", [](std::shared_ptr<HttpRequest> request) {

		HttpHeaders headers;
		headers.add(HttpCommon::Header::CONTENT_TYPE, "json");
		headers.add(HttpCommon::Header::CONTENT_LENGTH, "0");


		auto response = std::make_shared<HttpResponse>(200, "OK", std::move(headers));
		return response;
	});

	router->addRoute(HttpCommon::Verb::POST, "/register", [this](std::shared_ptr<HttpRequest> request) {
		const rapidjson::Document& body = request->document();
		const char* fieldValues[3];

		if (!assignFieldValue(&fieldValues[0], body, registerFields[0])) {
			return HttpResponse::createErrorResponse("Name is invalid or could not find field");
		}

		//we check if name is taken before reading the other fields , because we don't want to do operations
		//on a bad request
		if (dbHandler.isNameTaken(fieldValues[0])) 
			return HttpResponse::createErrorResponse("Name already taken");

		for (int8_t i = 1; i < 3; i++) {
			if (!assignFieldValue(&fieldValues[i], body, registerFields[i])) {
				return HttpResponse::createErrorResponse("Field is missing/invalid");
			}
		}

		//need to hash again here kk
		dbHandler.addUser(fieldValues[0], fieldValues[1], fieldValues[2]);

		jwtGenerator.setPayload(
			StringHelper::createBasicDoc(std::make_pair("name", fieldValues[0]))
		);


		rapidjson::Document jwtResponseBody = jwtGenerator.sucessfulJwtBody();
		rapidjson::StringBuffer buf;
		rapidjson::Writer w(buf);
		jwtResponseBody.Accept(w);


		HttpHeaders headers;
		headers.add(HttpCommon::Header::CONTENT_TYPE, "json");
		headers.add(HttpCommon::Header::CONTENT_LENGTH, std::to_string(buf.GetSize()));
		headers.add(HttpCommon::Header::HOST, hostName);

		return std::make_unique<HttpResponse>(200, "OK", std::move(headers), std::move(jwtResponseBody));
	});
	setRouter(std::move(router));
}
void Server::onNewMessage(std::shared_ptr<HttpRequest> req) {
	HttpsServer::onNewMessage(req);
	//ConsoleLog::info(req->toString());
}
