#pragma once
#include "Thumos/HttpRequest.hpp"
#include "Thumos/Detail/Http/HttpResponse.hpp"

typedef std::map<Verb, std::shared_ptr<HttpResponse>(*)(std::shared_ptr<HttpRequest>)> VerbHandlerMap;

namespace thm{
    class Resource {
    public:
            Resource(const std::string& name, const VerbHandlerMap& verbMap)
                    :_name(name) , _verbMap(verbMap)
            {}
            std::string_view name() const noexcept { return _name; }
            std::shared_ptr<HttpResponse> handle(std::shared_ptr<HttpRequest> request) const {
                    auto it = _verbMap.find(request->verb());
                    if (it == _verbMap.end()) {
                            return HttpResponse::createErrorResponse("No such method at the given resource");
                    }
                    else {
                            return it->second(request);
                    }
            }
    private:
            std::string _name;
            VerbHandlerMap _verbMap;
    };
}
