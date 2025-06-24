#include "Utility/FileWriter.hpp"
#include "asio.hpp"

namespace util{
    FileWriter::FileWriter(const std::string& path) {
            _path = path;
    }
    FileWriter::FileWriter(const std::filesystem::path& path) {
            _path = path;
    }

    void FileWriter::writeToFile(std::span<const char> data) {
            _file.open(_path);
            _file.write(data.data(), data.size());
            _file.close();
    }

    std::filesystem::path& FileWriter::path() noexcept { return _path; }
    const std::filesystem::path& FileWriter::path() const noexcept { return _path; }
}
