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
