#pragma once
#include "Thumos/Core/Message.hpp"
#include "Thumos/Detail/Http/HeaderList.hpp"
#include "Thumos/HttpBase.hpp"

namespace thm::detail{
    class HttpMessage : public core::Message {
        public:
            HttpMessage() = default;
            HttpMessage(const std::string& str);
            HttpMessage(const HeaderList& headers0, rapidjson::Document d0);
            const rapidjson::Document& document() const noexcept;
            const HeaderList& headers() const noexcept;
            static std::string documentToString(const rapidjson::Document& doc);
            static std::string documentToPrettyString(const rapidjson::Document& doc);
    protected:
            virtual void processFirstLine(const std::string& line);
            void processHeaders(const std::string& str, int32_t& pos);
            void processBody(const std::string& str, int32_t& pos);
    protected:
            HeaderList _headers;
            rapidjson::Document doc;
    };
}
