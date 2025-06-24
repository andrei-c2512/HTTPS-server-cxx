#include "Utility/FileHelper.hpp"

namespace util::file{
    constexpr CompressionType operator|(CompressionType lhs, CompressionType rhs) {
            return CompressionType(int(lhs) | int(rhs));
    }

    constexpr CompressionType operator&(CompressionType lhs, CompressionType rhs) {
            return CompressionType(int(lhs) & int(rhs));
    }

    constexpr CompressionType operator^(CompressionType lhs, CompressionType rhs) {
            return CompressionType(int(lhs) ^ int(rhs));
    }

    constexpr CompressionType operator~(CompressionType lhs) {
            return CompressionType(int(~lhs));
    }

    std::string_view getFileExtensionStr(const std::string_view fileName) noexcept {
            return fileName.substr(fileName.rfind('.'));
    }
}
