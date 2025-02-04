#define _CRT_SECURE_NO_DEPRECATE
#include "Server.hpp"
#include <cstdlib>
#include "RegisterHandler.hpp"



const std::string host     = "localhost";
const int16_t     dbPort   = 5432;
const std::string dbName   = "driveapp";
const std::string user     = "authserver";
const std::string password = std::getenv("STREAMING_APP_DB");

const std::string certificateFile           = "C:/Users/Andrei C/security/ca.crt";
const std::string certificatePrivateKeyFile = "C:/Users/Andrei C/security/ca.key";
const std::string jwtPrivateKeyFile         = "C:/Users/Andrei C/security/jwt_private_key.pem";
const std::string jwtPublicKeyFile          = "C:/Users/Andrei C/security/jwt_public_key.pem";


//this should be a path relative to the AuthServer program
const std::string webFolder = "Frontend/public";
const std::string storageFolder = "deliveryStorage";
Server::Server(int32_t port)
	:HttpsServer(port,
		certificateFile,
		certificatePrivateKeyFile, std::vector<std::string>(1, certificateFile))
{
	ctx.makeDbHandler(host, dbPort, dbName, user, password);
	ctx.makeJwtContext(jwtPrivateKeyFile, jwtPublicKeyFile);

	if (!std::filesystem::exists(storageFolder)) {
		std::filesystem::create_directory(storageFolder);
		ConsoleLog::info("Created storage folder");
	}

	ctx.makeWebDeliverer(storageFolder , webFolder);

	initRouter();
}

void Server::initRouter() {
	using namespace HttpCommon;

	auto router = std::make_unique<ListRouter>();
	ResourceHandling::RegisterResource* registerRes = new ResourceHandling::RegisterResource(&ctx);
	router->addResource("/register" , registerRes);
	
	setRouter(std::move(router));
}
void Server::onNewMessage(std::shared_ptr<HttpRequest> req) {
	HttpsServer::onNewMessage(req);
	//ConsoleLog::info(req->toString());
}
