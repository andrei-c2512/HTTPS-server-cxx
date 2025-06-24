#pragma once
#include "Thumos/HttpBase.hpp"


namespace thm::detail{
    class HeaderList {
    public:
            HeaderList();
            void add(const std::string_view key, const std::string_view val);
            void add(Header header, const std::string& val);
            //returns a map of the headers that are currently supported
            const std::map<Header, std::string>& supportedMap() const;
            //returns a map of the headers that are not supported
            const std::map<std::string, std::string>& unsupportedMap() const;
            static std::string headersToString(const HeaderList& headers);
    private:
            static constexpr int32_t avgLineLength = 40;
            std::map<Header, std::string> _supportedMap;
            std::map<std::string, std::string> _unsupportedMap;
    };
}
