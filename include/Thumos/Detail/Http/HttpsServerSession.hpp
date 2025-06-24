#pragma once
#include "Thumos/Core/SecureConnection.hpp"
#include "Thumos/HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpRequestReader.hpp"


namespace thm::detail{
    class HttpsServerSession : public core::SecureConnection<HttpRequest, detail::HttpResponse> {
    public:
            HttpsServerSession(asio::io_context& context0, asio::ssl::context& sslContext,
                    asio::ssl::stream<BasicSocket> stream,
                    util::ds::TsQueue<std::shared_ptr<HttpRequest>>& queue0)
                    : SecureConnection<HttpRequest, detail::HttpResponse>(context0, sslContext, std::move(stream), queue0)
            {
                    reader = new detail::HttpRequestReader<SslSocket>(_canWrite, queue0);
            }
    };
}
