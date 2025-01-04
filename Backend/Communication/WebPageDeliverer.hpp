#pragma once
#include "WebPageCodex.hpp"


namespace WebDelivery {
	class PageDeliverer {
	public:
		PageDeliverer(const std::string& webFolderPath)
			:codex(webFolderPath)
		{}
		std::string getFile(std::string_view fileName, std::vector<FileHelper::CompressionType> supported = { FileHelper::CompressionType::NONE}) {
			file.open(fileName.data());

			if (file.is_open()) {
				ConsoleLog::info("Sucessfully opened the file");
				file.seekg(std::ios::end);
				size_t fileSize = file.tellg();
				file.seekg(std::ios::beg);

				std::string fileData(fileSize, '\0');
				file.read(fileData.data(), fileSize);

				return fileData;


				file.close();
			}
			else {
				ConsoleLog::error("Could not open the file");
				return "";
			}
		}
	private:
		std::ifstream file;
		PageCodex codex;
	};
}
