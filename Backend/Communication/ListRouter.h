#pragma once
#include <string>
#include "RouterInterface.h"
#include <map>

class ListRouter : public RouterInterface {
public:
	ListRouter() = default;
	void addRoute(const std::string& route, 
		std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)> handler) override
	{
		routeHandlerMap.insert(std::make_pair(route , handler));
	}
	[[nodiscard]] std::shared_ptr<HttpResponse> handleRequest(const std::string& route, std::shared_ptr<HttpRequest> request) override{
		return routeHandlerMap[route](request);
	}
private:
	std::map <std::string, 
		std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)>> 
		routeHandlerMap;
};