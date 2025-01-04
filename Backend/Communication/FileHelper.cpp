#include "FileHelper.hpp"

FileHelper::FormatParser FileHelper::formatParser;

using namespace FileHelper;
FormatParser::FormatParser() {
	map.emplace("html", FileFormat::HTML);
	map.emplace("css", FileFormat::CSS);
	map.emplace("js", FileFormat::JAVA_SCRIPT);

	if (map.size() != int(FileHelper::FileFormat::COUNT)) {
		//ConsoleLog::warning("File format parser is not fully implemented.");
	}
}
FileFormat FormatParser::get(const std::string& str) const noexcept {
	auto it = map.find(str);
	if (it != map.end())
		return it->second;
	else
		return FileHelper::FileFormat::INVALID;
}


constexpr CompressionType FileHelper::operator|(CompressionType lhs, CompressionType rhs) {
	return CompressionType(int(lhs) | int(rhs));
}

constexpr CompressionType FileHelper::operator&(CompressionType lhs, CompressionType rhs) {
	return CompressionType(int(lhs) & int(rhs));
}

constexpr CompressionType FileHelper::operator^(CompressionType lhs, CompressionType rhs) {
	return CompressionType(int(lhs) ^ int(rhs));
}

constexpr CompressionType FileHelper::operator~(CompressionType lhs) {
	return CompressionType(int(~lhs));
}

FileFormat FileHelper::getFileFormat(const std::string& str) noexcept {
	size_t pos = str.rfind('.');
	return formatParser.get(str.substr(pos + 1));
}