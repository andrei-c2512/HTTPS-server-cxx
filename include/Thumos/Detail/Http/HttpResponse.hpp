#pragma once
#include "Thumos/Detail/Http/HttpMessage.hpp"


namespace thm::detail{
    class HttpResponse : public HttpMessage {
    public:
            HttpResponse() = default;
            HttpResponse(const std::string& str, int32_t id = 0);
            HttpResponse(int32_t statusCode, const std::string& phrase,
                    const HeaderList& headers, rapidjson::Document d0 = {}, int32_t id = 0);

            HttpResponse(Version version, int32_t statusCode, const std::string& phrase,
                    const HeaderList& headers, rapidjson::Document d0 = {} ,  int32_t id = 0);

            static std::string responseFirstLine(Version version, int32_t statusCode, const std::string& phrase);
            std::string toString() const override;
            Version version() const noexcept;
            int32_t statusCode() const noexcept;
            std::string phrase() const noexcept; 
            static std::unique_ptr<HttpResponse> createErrorResponse(const std::string_view error);
    protected:
            void processFirstLine(const std::string& line) override;
    private:
            Version _version;
            int32_t _statusCode;
            std::string _phrase;
    };

    typedef std::shared_ptr<HttpResponse> ResponsePtr;
}
