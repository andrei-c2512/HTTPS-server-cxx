#pragma once
#include "ConstexprMap.hpp"
#include "Common.hpp"
#include "StringViewArray.hpp"

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
		BROTLI = 1 << 4 ,
		COUNT = 5
	};


	constexpr StringViewArray<size_t(CompressionType::COUNT)> compressionNameArr = { "default" , "huffman" , "gzip" , "zip" , "brotli" };

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

	inline FileFormat toFileExtension(const std::string_view fileExtension) noexcept {
		auto it = fileFormatMap.at(fileExtension);
		if (it == fileFormatMap.end()) {
			return FileFormat::INVALID;
		}
		else
			return it->second;
	}

	inline std::string_view getFileExtensionStr(const std::string_view fileName) noexcept;
	inline std::string fileExtensionString(const std::filesystem::path& path) noexcept {
		std::string str = path.string();
		return str.substr(str.rfind('.'));;
	}

}