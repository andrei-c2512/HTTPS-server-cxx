#include "ResourceManager.hpp"

ResourceManager::ResponsePtr ResourceManager::Dash::GET_dash(RequestPtr request) {
	HttpHeaders headers;
	headers.add(HttpCommon::Header::CONTENT_TYPE, "json");
	headers.add(HttpCommon::Header::CONTENT_LENGTH, "0");


	auto response = std::make_shared<HttpResponse>(200, "OK", std::move(headers));
	return response;
}