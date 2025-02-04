#pragma once
#include <string>
#include <functional>
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "ResourceHandler.hpp"



class RouterInterface {
public:
	RouterInterface() = default;
	virtual void addResource(const std::string& name , ResourceHandler* resource) = 0;
	[[nodiscard]] virtual std::shared_ptr<HttpResponse> handleRequest( std::shared_ptr<HttpRequest> request) const = 0;
};