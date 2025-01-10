#include "FileHelper.hpp"

using namespace FileHelper;

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

std::string_view FileHelper::getFileExtensionStr(const std::string_view fileName) noexcept {
	return fileName.substr(fileName.rfind('.'));
}
FileFormat FileHelper::toFileExtension(const std::string_view fileName) {
	auto it = FileHelper::fileFormatMap.at(FileHelper::getFileExtensionStr(fileName));
	if (it == FileHelper::fileFormatMap.end()) {
		return FileHelper::FileFormat::INVALID;
	}
	else
		return it->second;
}
	