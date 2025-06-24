#include "Thumos/Detail/Http/HttpFilter.hpp"


namespace thm::detail{
        HttpFilter::HttpFilter()
        {}
        //returns the status code associated with the error that occurs. If there isn't any , then it return 100
        [[nodiscard]] std::pair<StatusCode, std::string> HttpFilter::filter(const HeaderList& headers) {
                std::pair<StatusCode, std::string> result = validResponse;

                if (contentFilterEnabled) {
                        result = contentTypeFilter(headers);
                }


                //I arranged this in a pretty interesting way. So if the message does in fact contain a JWT , it will be returned ,
                // along with the OK status code
                if (jwtFilterEnabled) {
                        result = jwtFilter(headers);

                        if (result.first != StatusCode::CONTINUE)
                                return result;
                }

                return result;
        }
        void HttpFilter::enableJWTFilter(bool state) {
                jwtFilterEnabled = state;
        }
        void HttpFilter::enableContentFilter(bool state, ContentType type) {
                contentFilterEnabled = state;
                contentType = type;
        }
        std::pair<StatusCode, std::string> HttpFilter::jwtFilter(const HeaderList& headers) {
                const auto& map = headers.supportedMap();
                auto it = map.find(Header::AUTHORIZATION);
                if (it == map.end())
                        return std::make_pair(StatusCode::UNAUTHORIZED , "Did not find authorization header");
                else
                {
                        size_t keyword1 = it->second.find(authKeyword1);
                        if (keyword1 == std::string::npos)
                                return std::make_pair(StatusCode::BAD_REQUEST, "Invalid authorization data");
                        else {
                                return std::make_pair(StatusCode::CONTINUE, it->second.substr(keyword1 + strlen(authKeyword1)));
                        }
                }
        }
        std::pair<StatusCode, std::string> HttpFilter::contentTypeFilter(const HeaderList& headers) {
                const auto& map = headers.supportedMap();
                auto it = map.find(Header::CONTENT_TYPE);
                if (it == map.end())
                        return std::make_pair(StatusCode::BAD_REQUEST , "Did not find content type header");
                else {
                        //mapping the extracted type to the content type
                        auto localContentType = toContentType(it->second);
                        if (contentType == ContentType::INVALID) {
                                return std::make_pair(StatusCode::BAD_REQUEST,
                                        "Invalid/badly formatted content type header. ");
                        }
                        else if (contentType != localContentType) {
                                return std::make_pair(StatusCode::BAD_REQUEST, "Incorrect format");
                        }
                        else {
                                return validResponse;
                        }
                        
                }
        }
}
