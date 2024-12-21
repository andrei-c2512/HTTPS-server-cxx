#pragma once
#include <string>
#include <functional>
#include "HttpResponse.h"
#include "HttpRequest.h"

class RouterInterface {
public:
	RouterInterface() = default;
	virtual void addRoute(const std::string& route, 
		//this shi ugly as hell
		std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)> handler) = 0;

	[[nodiscard]] virtual std::shared_ptr<HttpResponse> handleRequest(const std::string& route, std::shared_ptr<HttpRequest> request) = 0;
};