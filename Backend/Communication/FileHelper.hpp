#pragma once
#include "ConstexprMap.hpp"
#include <string_view>

namespace FileHelper {
	enum class FileFormat : size_t {
		HTML,
		CSS,
		JAVA_SCRIPT,
		COUNT,
		INVALID
	};

	enum class CompressionType {
		NONE = 1 << 0,
		HUFFMAN = 1 << 1,
		GZIP = 1 << 2,
		ZIP = 1 << 3,
		BROTLI = 1 << 4
	};


	//implementing the bitwise operations for the mask cuz it will be annoying to always cast shi
	constexpr CompressionType operator|(CompressionType lhs, CompressionType rhs);
	constexpr CompressionType operator&(CompressionType lhs, CompressionType rhs);
	constexpr CompressionType operator^(CompressionType lhs, CompressionType rhs);
	constexpr CompressionType operator~(CompressionType lhs);

	inline ConstexprMap<std::string_view, FileFormat, (size_t)FileFormat::COUNT> fileFormatMap = {
		{ std::make_pair<std::string_view , FileFormat>("html" , FileFormat::HTML)  ,
		  std::make_pair<std::string_view , FileFormat>("css" , FileFormat::CSS),
		  std::make_pair<std::string_view , FileFormat>("js" , FileFormat::JAVA_SCRIPT)
		}
	};

	FileFormat toFileExtension(const std::string_view fileName);
	std::string_view getFileExtensionStr(const std::string_view fileName) noexcept;

}