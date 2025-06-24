#pragma once
#include "Thumos/Detail/Http/HeaderList.hpp"


namespace thm::detail{
    //this class is for filtering bad formated/incomplete/bs requests and responses
    class HttpFilter {
    public:
            HttpFilter();
            [[nodiscard]] std::pair<StatusCode, std::string> filter(const HeaderList& headers);
            void enableJWTFilter(bool state);
            void enableContentFilter(bool state, ContentType type);
    private:
            std::pair<StatusCode, std::string> jwtFilter(const HeaderList& headers); 
            std::pair<StatusCode, std::string> contentTypeFilter(const HeaderList& headers);
    private:
            static constexpr auto authKeyword1 = "Bearer ";
            static constexpr auto validResponse = std::make_pair(StatusCode::CONTINUE, "OK");

            bool jwtFilterEnabled = false;

            bool contentFilterEnabled = false;
            ContentType contentType = ContentType::JSON;
    };

}
