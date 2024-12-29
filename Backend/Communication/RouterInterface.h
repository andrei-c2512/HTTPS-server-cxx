#pragma once
#include <string>
#include <functional>
#include "HttpResponse.h"
#include "HttpRequest.h"

class RouterInterface {
public:
	RouterInterface() = default;
	virtual void addRoute(HttpCommon::Verb verb , const std::string& route, 
		std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)> handler) = 0;

	[[nodiscard]] virtual std::shared_ptr<HttpResponse> handleRequest( std::shared_ptr<HttpRequest> request) = 0;
};