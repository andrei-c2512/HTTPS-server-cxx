#include "AuthServer/HandlingContext.hpp"

using namespace ResourceHandling;

void HandlingContext::makeJwtContext(const std::string& privateKeyFile, const std::string& publicKeyFile) noexcept {
	_jwtGenerator = std::make_unique<thm::jwt::Generator>(privateKeyFile);
	_jwtValidator = std::make_unique<thm::jwt::Validator>(publicKeyFile);
}
void HandlingContext::makeWebDeliverer(const std::string& storageFolder , const std::string& webFolder) noexcept {
	_wpDeliverer = std::make_unique<thm::web::PageDeliverer>(storageFolder , webFolder);
}
void HandlingContext::makeDbHandler(const std::string& localHost, int16_t port, const std::string& dbName,
	const std::string& user, const std::string& password) noexcept {
	_dbHandler = std::make_unique<DatabaseHandler>(localHost, port, dbName, user, password);
}

thm::jwt::Generator& HandlingContext::jwtGenerator() const noexcept {
	assert(_jwtGenerator);
	return *_jwtGenerator; 
}
thm::jwt::Validator& HandlingContext::jwtValidator() const noexcept {
	assert(_jwtValidator);
	return *_jwtValidator;
}
thm::web::PageDeliverer& HandlingContext::pageDeliverer() const noexcept {
	assert(_wpDeliverer);
	return *_wpDeliverer;
}
DatabaseHandler& HandlingContext::dbHandler() const noexcept {
	assert(_dbHandler);
	return *_dbHandler;
}
