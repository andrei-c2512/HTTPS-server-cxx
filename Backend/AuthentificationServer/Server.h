#pragma once
#include "HttpsServer.h"
#include "ListRouter.h"
#include "JWTgenerator.h"
#include "JWTverifier.h"
#include "DatabaseHandler.h"

class Server : public HttpsServer {
public:
	Server(int32_t port);
protected:
	void onNewMessage(std::shared_ptr<HttpRequest> req) override;
	void initRouter() override;
private:
	static bool assignFieldValue(const char** dest, const rapidjson::Document& body, const char* field);
private:
	JWT::Generator jwtGenerator;
	JWT::Verifier jwtVerifier;
	DatabaseHandler dbHandler;

	const char* registerFields[3] = { "name" , "email" , "password" };
	const char* hostName = "localhost";
};
