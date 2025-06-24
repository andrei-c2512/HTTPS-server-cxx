#include "Thumos/Detail/Http/HttpMessage.hpp"

namespace thm::detail{
    HttpMessage::HttpMessage(const std::string& str) {
            doc.SetObject();
            int32_t i = 0;
            std::string firstLine = util::str::nextLine(str, i);

            /* TO DO: FIX THIS SHIT BY SEPARATING STUFF */
            processFirstLine(firstLine);
            /* YOU CANNOT CALL VIRUAL FUNC IN THE CONSTRUCTOR */
            processHeaders(str, i);
            processBody(str, i);
    }
    HttpMessage::HttpMessage(const HeaderList& headers0, rapidjson::Document d0)
            :_headers(headers0), doc(std::move(d0))
    {}
    const rapidjson::Document& HttpMessage::document() const noexcept { return doc; }
    const HeaderList& HttpMessage::headers() const noexcept { return _headers; }
    std::string HttpMessage::documentToString(const rapidjson::Document& doc) {
            rapidjson::StringBuffer buf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
            doc.Accept(writer);

            return buf.GetString();
    }
    std::string HttpMessage::documentToPrettyString(const rapidjson::Document& doc) {
            rapidjson::StringBuffer buf;
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
            doc.Accept(writer);

            return buf.GetString();
    }

    void HttpMessage::processHeaders(const std::string& str, int32_t& pos) {
        /* TO DO: IMPLEMENT */
    }
    void HttpMessage::processBody(const std::string& str, int32_t& pos) {
        /* TO DO: IMPLEMENT */
    }

    void HttpMessage::processFirstLine(const std::string& line){
        /* TO DO: LEAVE THIS SHIT TO THE READER CLASS LMAO */
    }
}
