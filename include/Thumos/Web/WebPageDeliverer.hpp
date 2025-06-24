#pragma once
#include "Thumos/Web/WebPageCodex.hpp"


namespace thm::web{
	class PageDeliverer {
	public:
		PageDeliverer(const std::string& storagePath , const std::string& webFolderPath);
		std::string getFile(std::string_view fileName, std::vector<file::CompressionType> supported = { file::CompressionType::NONE});
	private:
		std::ifstream file;
		PageCodex codex;
	};
}
