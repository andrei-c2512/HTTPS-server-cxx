#pragma once
#include "Thumos/Routing/RouterInterface.hpp"
#include "Thumos/Routing/ResourceHandler.hpp"
#include <map>
#include <string>

namespace thm{
    class ListRouter : public RouterInterface {
    public:
            ListRouter() = default;
            ~ListRouter() {
                    for (auto& [key, value] : resourceMap) {
                            delete value;
                            value = nullptr;
                    }
            }
            ListRouter(const ListRouter&) = delete;
            ListRouter& operator=(const ListRouter&) = delete;
            ListRouter(ListRouter&& l) {
                    resourceMap = l.resourceMap;
                    l.resourceMap.clear();
            }
            ListRouter& operator=(ListRouter&& l) {
                    resourceMap = l.resourceMap;
                    l.resourceMap.clear();
                    return *this;
            }
            void addResource(const std::string& name , ResourceHandler* res) override
            {
                    resourceMap.emplace(name, res);
            }
            [[nodiscard]] std::shared_ptr<detail::HttpResponse> handleRequest(std::shared_ptr<HttpRequest> request) const override{

                    auto resMapIt = resourceMap.find(request->URI());
                    if (resMapIt != resourceMap.end()) {
                            return resMapIt->second->handle(request);
                    }
                    else
                            return detail::HttpResponse::createErrorResponse("Invalid resource");
            }
    private:
            std::map<std::string, ResourceHandler*> resourceMap;
    };
}
