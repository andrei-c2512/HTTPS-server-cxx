#include "Utility/FileReader.hpp"


namespace util{
    FileReader::FileReader(const std::string& rootFolder) {
            _path = rootFolder;
    }
    FileReader::FileReader(const std::filesystem::path& path) {
            _path = path;
    }
    //reads a file from the current directory
    [[nodiscard]] std::string FileReader::readFile() noexcept {
            file.open(_path , std::ios::binary | std::ios::ate);
            if (!file) {
                    log::error("Failed to open file");
            }
            std::streamsize fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            
            std::string buffer;
            buffer.reserve(fileSize);
            if (!file.read(buffer.data(), fileSize)) {
                    log::error("Failed to read the file");
            }
            
            file.close();
            return buffer;
    }

    [[nodiscard]] std::string FileReader::readFile(const std::string_view path) noexcept {
            _path = path;
            return readFile();
    }

    std::filesystem::path& FileReader::path() noexcept { return _path; }
    const std::filesystem::path& FileReader::path() const noexcept { return _path; }
}
