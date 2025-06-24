#pragma once
#include "Common.hpp"

namespace util::log{
        constexpr int32_t lineLimit = 50;
        std::string endl();
        void message(const std::string_view str);
        void error(const std::string_view str);
        void warning(const std::string_view str);
        void info(const std::string_view str);
        void writeText(const std::string_view str);
        std::string_view writeLine(const std::string_view str , int32_t& start);
        /* This function was made for the 'asio::error_code' class. I am tired of writing if-else */
        template<typename Exception>
        bool handleError(Exception& ec, const std::string_view sucessMsg , const std::string& errorMsg) {
                if (!ec) {
                        info(sucessMsg);
                        return false;
                }
                else
                {
                        error(errorMsg + " : " + ec.message());
                        return true;
                }
        }
        void printColoredText(const std::string_view msg, const std::string_view color);
        void notImplemented(const std::experimental::source_location& loc = std::experimental::source_location::current());
}
