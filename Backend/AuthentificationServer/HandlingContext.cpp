#pragma once
#include "HandlingContext.hpp"

using namespace ResourceHandling;

void HandlingContext::makeJwtContext(const std::string& privateKeyFile, const std::string& publicKeyFile) noexcept {
	_jwtGenerator = std::make_unique<JWT::Generator>(privateKeyFile);
	_jwtValidator = std::make_unique<JWT::Validator>(publicKeyFile);
}
void HandlingContext::makeWebDeliverer(const std::string& storageFolder , const std::string& webFolder) noexcept {
	_wpDeliverer = std::make_unique<WebDelivery::PageDeliverer>(storageFolder , webFolder);
}
void HandlingContext::makeDbHandler(const std::string& localHost, int16_t port, const std::string& dbName,
	const std::string& user, const std::string& password) noexcept {
	_dbHandler = std::make_unique<DatabaseHandler>(localHost, port, dbName, user, password);
}

JWT::Generator& HandlingContext::jwtGenerator() const noexcept {
	assert(_jwtGenerator);
	return *_jwtGenerator; 
}
JWT::Validator& HandlingContext::jwtValidator() const noexcept {
	assert(_jwtValidator);
	return *_jwtValidator;
}
WebDelivery::PageDeliverer& HandlingContext::pageDeliverer() const noexcept {
	assert(_wpDeliverer);
	return *_wpDeliverer;
}
DatabaseHandler& HandlingContext::dbHandler() const noexcept {
	assert(_dbHandler);
	return *_dbHandler;
}