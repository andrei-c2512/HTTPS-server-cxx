#pragma once
#include "Log.hpp"


namespace util{
    class FileReader {
    public:
            //root from where the reading will start
            FileReader(const std::string& rootFolder);
            FileReader(const std::filesystem::path& path);
            //reads a file from the current directory
            [[nodiscard]] std::string readFile() noexcept;
            [[nodiscard]] std::string readFile(const std::string_view path) noexcept;
            std::filesystem::path& path() noexcept; 
            const std::filesystem::path& path() const noexcept;
    private:
            std::filesystem::path _path;
            std::ifstream file;
    };
}
