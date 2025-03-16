#pragma once
#include "FileHelper.hpp"
#include "Common.hpp"
#include <span>


class DataCompressor {
public:
	DataCompressor() = default;
	DataCompressor(std::span<char> data , FileHelper::CompressionType type) {
		init(data, type);
	}
	void init(std::span<const char> data0, FileHelper::CompressionType type0) {
		data = data0;
		type = type0;
	}
	[[nodiscard]] std::vector<char> compress() const {
		switch (type) {
		case FileHelper::CompressionType::NONE:
			return std::vector<char>(std::begin(data) , std::end(data));
		default:
			return {'f' , 'l'};
		}
	}
	
private:
	std::span<const char> data;
	FileHelper::CompressionType type;
};