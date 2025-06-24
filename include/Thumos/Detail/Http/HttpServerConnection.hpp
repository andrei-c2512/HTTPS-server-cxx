#pragma once
#include "Thumos/Detail/Http/HttpMessage.hpp"
#include "Thumos/Detail/Http/HttpRequestReader.hpp"
#include "Thumos/Core/BasicConnection.hpp"

//if you are a server and want to handle connections from clients , use this
//this one is ready to read incoming requests(since servers respond to requests)
namespace thm::detail{
    class HttpServerConnection : public BasicConnection<HttpRequest, HttpResponse> {
    public:
            HttpServerConnection(asio::io_context& context0, BasicSocket socket0, util::ds::TsQueue<std::shared_ptr<HttpRequest>>& queue)
                    :BasicConnection<HttpRequest , HttpResponse>(context0, std::move(socket0), queue)
            {
                    // a Http reader of type unsafe socket
                    reader = new HttpRequestReader<BasicSocket>(_canWrite, queue);
            }
    protected:
            using BasicConnection<HttpRequest, Internal::HttpResponse>::socket;
            using BasicConnection<HttpRequest, HttpResponse>::reader;
    };
}
