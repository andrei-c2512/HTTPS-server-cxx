#pragma once
#include "ConsoleLog.hpp"


class FileReader {
public:
	//root from where the reading will start
	FileReader(const std::string& rootFolder) {
		_path = rootFolder;
	}
	FileReader(const std::filesystem::path& path) {
		_path = path;
	}
	//reads a file from the current directory
	[[nodiscard]] std::string readFile() noexcept {
		file.open(_path , std::ios::binary | std::ios::ate);
		if (!file) {
			ConsoleLog::error("Failed to open file");
		}
		std::streamsize fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		
		std::string buffer;
		buffer.reserve(fileSize);
		if (!file.read(buffer.data(), fileSize)) {
			ConsoleLog::error("Failed to read the file");
		}
		
		file.close();
		return buffer;
	}

	[[nodiscard]] std::string readFile(const std::string_view path) noexcept {
		_path = path;
		return readFile();
	}

	std::filesystem::path& path() noexcept { return _path; }
	const std::filesystem::path& path() const noexcept { return _path; }
private:
	std::filesystem::path _path;
	std::ifstream file;
};