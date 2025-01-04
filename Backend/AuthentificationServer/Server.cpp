#define _CRT_SECURE_NO_DEPRECATE
#include "Server.hpp"
#include "ResourceManager.hpp"
#include <cstdlib>
const std::string host = "localhost";
const int16_t     dbPort = 5432;
const std::string dbName = "driveapp";
const std::string user = "authserver";
const std::string password = std::getenv("STREAMING_APP_DB");

const std::string certificateFile = "C:/Users/Andrei C/security/ca.crt";
const std::string certificatePrivateKeyFile = "C:/Users/Andrei C/security/ca.key";
const std::string jwtPrivateKeyFile = "C:/Users/Andrei C/security/jwt_private_key.pem";
const std::string jwtPublicKeyFile = "C:/Users/Andrei C/security/jwt_public_key.pem";


//this should be a path relative to the AuthServer program
const std::string webFolder = "Frontend/public";

Server::Server(int32_t port)
	:HttpsServer(port,
		certificateFile,
		certificatePrivateKeyFile, std::vector<std::string>(1, certificateFile)),
	dbHandler(host, dbPort, dbName, user, password),
	jwtGenerator(jwtPrivateKeyFile),
	jwtValidator(jwtPublicKeyFile),
	webPageDeliverer(webFolder)
{
	ResourceManager::ctx.jwtValidator = &jwtValidator;
	ResourceManager::ctx.jwtGenerator = &jwtGenerator;
	ResourceManager::ctx.dbHandler    = &dbHandler;
	ResourceManager::ctx.wpDeliverer = &webPageDeliverer;
	initRouter();
}

void Server::initRouter() {
	using namespace HttpCommon;

	auto router = std::make_unique<ListRouter>();
	
	VerbHandlerMap registerMap;
	registerMap.emplace(Verb::POST, &ResourceManager::Auth::POST_register);
	registerMap.emplace(Verb::GET, &ResourceManager::Auth::GET_register);
	Resource reg("/register", registerMap);

	VerbHandlerMap dashMap;
	dashMap.emplace(Verb::GET, &ResourceManager::Dash::GET_dash);
	Resource dash("/", dashMap);


	router->addResource(reg);
	router->addResource(dash);
	setRouter(std::move(router));
}
void Server::onNewMessage(std::shared_ptr<HttpRequest> req) {
	HttpsServer::onNewMessage(req);
	//ConsoleLog::info(req->toString());
}
