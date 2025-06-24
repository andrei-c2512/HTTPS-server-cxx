#pragma once
#include "Thumos/Detail/Http/HttpResponse.hpp"
#include "Thumos/HttpRequest.hpp"
#include "Thumos/Routing/ResourceHandler.hpp"



namespace thm{
    class RouterInterface {
    public:
            RouterInterface() = default;
            virtual void addResource(const std::string& name , ResourceHandler* resource) = 0;
            [[nodiscard]] virtual std::shared_ptr<detail::HttpResponse> handleRequest( std::shared_ptr<HttpRequest> request) const = 0;
    };
}
