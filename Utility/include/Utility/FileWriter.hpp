#pragma once
#include "Common.hpp"

namespace util{
    class FileWriter {
    public:
            FileWriter(const std::string& path);
            FileWriter(const std::filesystem::path& path);
            void writeToFile(std::span<const char> data);
            std::filesystem::path& path() noexcept;
            const std::filesystem::path& path() const noexcept;
    private:
            std::ofstream _file;
            std::filesystem::path _path;
    };
}
