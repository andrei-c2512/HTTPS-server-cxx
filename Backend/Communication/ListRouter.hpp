#pragma once
#include <string>
#include "RouterInterface.hpp"
#include <map>

typedef std::map <std::string,
	std::function<std::shared_ptr<HttpResponse>(std::shared_ptr<HttpRequest>)>> RouteHandleMap;

class ListRouter : public RouterInterface {
public:
	ListRouter() = default;
	void addResource(Resource res) override
	{
		resourceMap.emplace(res.name(), res);
	}
	[[nodiscard]] std::shared_ptr<HttpResponse> handleRequest(std::shared_ptr<HttpRequest> request) const override{

		auto resMapIt = resourceMap.find(request->URI());
		if (resMapIt != resourceMap.end()) {
			return resMapIt->second.handle(request);
		}
		else
			return HttpResponse::createErrorResponse("Invalid resource");
	}
private:
	std::map<std::string, Resource> resourceMap;
};