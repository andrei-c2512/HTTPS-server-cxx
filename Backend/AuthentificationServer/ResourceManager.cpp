#include "ResourceManager.hpp"

namespace ResourceManager {
	HandlingContext ctx;
	const char* hostName = "localhost";
}

namespace ResourceManager::Auth {
	const char* registerFields[3] = { "name" , "email" , "password" };
}