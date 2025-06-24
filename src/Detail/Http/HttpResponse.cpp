#include "Thumos/Detail/Http/HttpResponse.hpp"


namespace thm::detail{ 
        HttpResponse::HttpResponse(const std::string& str, int32_t id)
                :HttpMessage(str) 
        {
                setUserId(id);
        }
        HttpResponse::HttpResponse(int32_t statusCode, const std::string& phrase,
                const HeaderList& headers, rapidjson::Document d0, int32_t id)
                :HttpMessage(headers, std::move(d0)), _version(defaultVersion) , _statusCode(statusCode), _phrase(phrase)
        {
                setUserId(id);
        }

        HttpResponse::HttpResponse(Version version, int32_t statusCode, const std::string& phrase,
                const HeaderList& headers, rapidjson::Document d0 ,  int32_t id )
                :HttpMessage(headers, std::move(d0)), _version(version), _statusCode(statusCode), _phrase(phrase)
        {
                setUserId(id);
        }

        std::string HttpResponse::responseFirstLine(Version version, int32_t statusCode, const std::string& phrase) {
                return versionArr.copyAt((int8_t)version) + ' ' +
                        std::to_string(statusCode) + ' ' + 
                        phrase + '\n';
        }
        std::string HttpResponse::toString() const {
                if (doc.MemberCount() != 0) {
                        return responseFirstLine(_version, _statusCode, _phrase) +
                                HeaderList::headersToString(_headers) +
                                HttpMessage::documentToString(doc);
                }
                else {
                        return responseFirstLine(_version, _statusCode, _phrase) +
                                HeaderList::headersToString(_headers);
                }
        }
        Version HttpResponse::version() const noexcept { return _version; }
        int32_t HttpResponse::statusCode() const noexcept { return _statusCode; }
        std::string HttpResponse::phrase() const noexcept { return _phrase; }

        std::unique_ptr<HttpResponse> HttpResponse::createErrorResponse(const std::string_view error) {
                rapidjson::Document body;
                body.SetObject();
                rapidjson::Value errorValue(error.data(), body.GetAllocator());

                body.AddMember("error", errorValue, body.GetAllocator());
                HeaderList headers;
                headers.add(Header::CONTENT_TYPE, "application/json");
                headers.add(Header::CONTENT_LENGTH, std::to_string(util::str::jsonCharLength(body)));

                return std::make_unique<HttpResponse>(400 ,  "Bad request", std::move(headers), std::move(body));
        }

        void HttpResponse::processFirstLine(const std::string& line) {
        }
}
