#include "Thumos/Detail/Http/HeaderList.hpp"


namespace thm::detail{
    HeaderList::HeaderList() 
    {}

    void HeaderList::add(const std::string_view key, const std::string_view val) {
            auto header = toHeader(key);
            if (header != Header::INVALID) {
                    _supportedMap.emplace(header, val.data());
            }
            else {
                    _unsupportedMap.emplace(key, val.data());
            }
    }
    void HeaderList::add(Header header, const std::string& val) {
            _supportedMap.emplace(header, val);
    }
    //returns a map of the headers that are currently supported
    const std::map<Header, std::string>& HeaderList::supportedMap() const {
            return _supportedMap;
    }
    //returns a map of the headers that are not supported
    const std::map<std::string, std::string>& HeaderList::unsupportedMap() const {
            return _unsupportedMap;
    }
    std::string HeaderList::headersToString(const HeaderList& headers) {
            util::log::warning("Headers may not be shown in the way they were sent because the function shows" 
                    "supported headers first and then the unsupported headers");

            const std::map<Header, std::string>& supportedMap = headers.supportedMap();
            const auto& unsupportedMap = headers.unsupportedMap();

            std::string headerText;
            headerText.reserve(avgLineLength * (supportedMap.size() + unsupportedMap.size()));

            std::string line;
            line.reserve(avgLineLength);
            for (const auto& [key, value] : supportedMap) {
                    std::string keyStr = headerArr.copyAt((int8_t)key);
                    line.append(keyStr);
                    line.append(":");
                    line.append(value);
                    line.append("\n");

                    headerText.append(line);
                    line.clear();
            }

            for (const auto& [key, value] : unsupportedMap) {
                    line.append(key);
                    line.append(":");
                    line.append(value);
                    line.append("\n");

                    headerText.append(line);
                    line.clear();
            }


                return headerText;
        }
}
