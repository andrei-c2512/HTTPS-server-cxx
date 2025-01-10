#pragma once
#include "HttpCommon.hpp"
#include "WebComponent.hpp"

//this class scans a folder and categorizes all of them by extension 
namespace WebDelivery {
	class PageCodex {
	public:
		PageCodex(const std::string& folderPath0)
			:folderPath(folderPath0)
		{
			if (std::filesystem::exists(folderPath) == false) {
				ConsoleLog::error("Invalid web page folder");
			}
			else
			{
				componentMatrix.resize(int(FileHelper::FileFormat::COUNT));
				for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
					if (std::filesystem::is_regular_file(entry)) {
						std::string fileName = entry.path().filename().string();
						
						//auto format = FileHelper::fileFormatMap.at(fileName);
						auto f = HttpCommon::headerMap.at("Accept");
				
					}
				}
			}


		}

		//returns empty string if not found
		std::string getPage(const std::string& fileName, FileHelper::FileFormat format) {

		}
	private:
		std::string folderPath;

		std::vector<std::vector<Component>> componentMatrix;
	};
}
