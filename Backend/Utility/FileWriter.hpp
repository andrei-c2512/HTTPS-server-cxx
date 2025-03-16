#include "Common.hpp"


class FileWriter {
public:
	FileWriter(const std::string& path) {
		_path = path;
	}
	FileWriter(const std::filesystem::path& path) {
		_path = path;
	}

	void writeToFile(std::span<const char> data) {
		_file.open(_path);
		_file.write(data.data(), data.size());
		_file.close();
	}

	std::filesystem::path& path() noexcept { return _path; }
	const std::filesystem::path& path() const noexcept { return _path; }
private:
	std::ofstream _file;
	std::filesystem::path _path;
};