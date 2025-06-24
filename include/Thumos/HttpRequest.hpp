#pragma once
#include "Thumos/HttpBase.hpp"
#include "Thumos/Detail/Http/HeaderList.hpp"
#include "Thumos/Detail/Http/HttpMessage.hpp"

namespace thm{
    class HttpRequest : public detail::HttpMessage {
    public:
            HttpRequest() = default;
            HttpRequest(const std::string& str , int32_t id = 0)
                    :HttpMessage(str) 
            {
                    setUserId(id);
                    /*int32_t i = 0;
                    int32_t strCursor = 0;
                    int32_t last = 0;

                    char breakChar = ' ';
                    for (; strCursor < str.size(); strCursor++) {
                            if (str[strCursor] == breakChar)
                            {
                                    reqTypeStorage[i] = str.substr(last, i - last);
                                    last = i + 1;
                                    i++;
                                    if (i == 2)
                                            breakChar = '\n';
                                    else if (i == 3)
                                            break;
                            }
                    }
                    extractHeaders(str, strCursor);*/
            }
            HttpRequest(Verb v, const std::string& URI0,
                    const detail::HeaderList& headers0, rapidjson::Document d0, int32_t id = 0)
                    :HttpMessage(headers0, std::move(d0)), _verb(v), _URI(URI0), _version(defaultVersion)
            {
                    setUserId(id);
            }
            HttpRequest(Verb v, const std::string& URI0, Version version0,
                    const detail::HeaderList& headers0, rapidjson::Document d0 , int32_t id = 0)
                    :HttpMessage(headers0, std::move(d0)), _verb(v), _URI(URI0), _version(version0)
            {
                    setUserId(id);
            }

            static std::string requestFirstLine(Verb verb , const std::string& URI  , Version version) {
                    return verbArr.copyAt((int8_t)verb) + ' ' +
                            URI + ' ' + 
                            versionArr.copyAt((int8_t)version) + '\n';
            }
            Verb verb() const noexcept { return _verb; }
            const std::string& URI() const noexcept { return _URI; }
            Version version() const noexcept { return _version; }
            
            //might implement later lol
            std::string scheme() const noexcept;
            std::string server() const noexcept;
            std::string path() const noexcept;

            std::string toString() const override {
                    if (doc.MemberCount() != 0) {
                            return requestFirstLine(_verb, _URI, _version) +
                                    detail::HeaderList::headersToString(_headers) +
                                    detail::HttpMessage::documentToString(doc);
                    }
                    else {
                            return requestFirstLine(_verb, _URI, _version) +
                                    detail::HeaderList::headersToString(_headers);
                    }
            }
    protected:
            void processFirstLine(const std::string& line) override {}
    private:
            void extractMethod();
            void extractUrl();
            void extractScheme();
            void extractServer();
            void extractPath();
            int32_t extractHeaders(const std::string& str, int32_t start);
    private:
            Verb _verb;
            std::string _URI;
            Version _version;
    };

    typedef std::shared_ptr<HttpRequest> RequestPtr;
}
