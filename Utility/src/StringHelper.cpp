#include "Utility/StringHelper.hpp"

namespace util::str{
    std::string nextLine(const std::string& str, int32_t& begin) {
            auto copy = begin;
            for (; begin < str.size(); begin++)
            {
                    if (str[begin] == '\n')
                    {
                            return str.substr(copy, begin++ - copy);
                    }
            } return "";
    }
    std::string nextLine(const std::string& str, int32_t& begin, int32_t end) {
            auto copy = begin;
            for (; begin < end; begin++)
            {
                    if (str[begin] == '\n')
                    {
                            return str.substr(copy, begin++ - copy);
                    }
            }
            return "";
    }
    std::string jsonToString(const rapidjson::Document& doc) {
            using namespace rapidjson;
            StringBuffer docBuffer;
            Writer<StringBuffer> writer(docBuffer);
            doc.Accept(writer);

            return docBuffer.GetString();
    }

    size_t jsonCharLength(const rapidjson::Document& doc) {
            using namespace rapidjson;
            StringBuffer docBuffer;
            Writer<StringBuffer> writer(docBuffer);
            doc.Accept(writer);

            return docBuffer.GetSize();
    }
}
