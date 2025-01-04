#pragma once
#include <string>
#include <map>

namespace FileHelper {
	enum class FileFormat {
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

	class FormatParser {
	public:
		FormatParser();
		FileFormat get(const std::string& str) const noexcept;
	private:
		std::map<std::string, FileFormat> map;
	};

	extern FormatParser formatParser;

	FileFormat getFileFormat(const std::string& str) noexcept;
}