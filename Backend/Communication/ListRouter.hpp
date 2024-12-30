#pragma once
#include <string>
#include "RouterInterface.hpp"
#include <map>

typedef std::map <std::string,
	std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)>> RouteHandleMap;

class ListRouter : public RouterInterface {
public:
	ListRouter() = default;
	void addRoute(HttpCommon::Verb verb , const std::string& route, 
		std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)> handler) override
	{
		verbMap[verb].insert(std::make_pair(route, handler));
	}
	[[nodiscard]] std::shared_ptr<HttpResponse> handleRequest(std::shared_ptr<HttpRequest> request) const override{
		auto verbMapIt = verbMap.find(request->verb());
		if (verbMapIt != verbMap.end()) {
			auto routeMapIt = verbMapIt->second.find(request->URI());
			if (routeMapIt != verbMapIt->second.end()) {
				return routeMapIt->second(request);
			}
			else
				return HttpResponse::createErrorResponse("Invalid route");
		}
		else
			return HttpResponse::createErrorResponse("Invalid verb");
	}
private:
	std::map<HttpCommon::Verb, RouteHandleMap> verbMap;
};