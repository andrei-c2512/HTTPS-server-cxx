#include "Utility/Log.hpp"

namespace util::log{
    std::string endl() {
            return '\n' + std::string(strlen("[MESSAGE]" + 1), ' ');
    }
    void message(const std::string_view str) {
            printColoredText("[MESSAGE]", "92");
            writeText(str);
    }
    void error(const std::string_view str){
            printColoredText("[ERROR]  ", "91");
            writeText(str);
    }
    void warning(const std::string_view str) {
            printColoredText("[WARNING]", "93");
            writeText(str);
    }
    void info(const std::string_view str) {
            printColoredText("[INFO]   ", "96");
            writeText(str);
    }
    void writeText(const std::string_view str) {
            std::string_view nextSequence = str.substr(0, lineLimit);
            nextSequence = nextSequence.substr(0, std::min(nextSequence.find('\n'), (size_t)lineLimit));

            std::cout << ' ' << nextSequence;
            std::cout << '\n';

            int32_t i = nextSequence.size();
            for (; i < str.size(); )
            {
                    nextSequence = writeLine(str , i);
                    i += nextSequence.size();
                    if (nextSequence.size() < lineLimit)
                            i++;
            }
    }
    std::string_view writeLine(const std::string_view str , int32_t& start) {
            std::string_view nextSequence = str.substr(start, lineLimit);
            nextSequence = nextSequence.substr(0, std::min(nextSequence.find('\n'), (size_t)lineLimit));

            std::cout << std::string(strlen("[MESSAGE]"), ' ')
                    << ' ' << nextSequence;

            std::cout << '\n';

            return nextSequence;
    }

    void printColoredText(const std::string_view msg, const std::string_view color) {
            std::cout << "\033[" << color << "m" << msg << "\033[0m";
    }
    void notImplemented(const std::experimental::source_location& location){ 
        std::cout << location.file_name() << ":" << location.line()
              << " [" << location.function_name() << "] " << " is not implemented" << "\n";
    }
}

