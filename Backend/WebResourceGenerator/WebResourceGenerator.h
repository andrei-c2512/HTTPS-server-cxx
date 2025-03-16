#pragma once
#include <filesystem>
#include <queue>
#include "FileHelper.hpp"
#include "ConsoleLog.hpp"
#include <fstream>

//vim test
//this is a file that generates another file with a class where each member has the name
//of a frontend file
class WebResourceGenerator {
public:
	WebResourceGenerator(std::filesystem::path webFolderPath  , std::filesystem::path outputPath0 , std::string generatedFileName = "WebResource.hpp")
		:projectDir(webFolderPath) , outputFileName(generatedFileName) , outputPath(outputPath0)
	{}
	void capturePaths() {
		std::queue<std::filesystem::path> dirQueue;
		dirQueue.emplace(projectDir);

		while (dirQueue.empty() == false) {
			const auto& dir = dirQueue.front();
			for (const auto& entry : std::filesystem::directory_iterator(dir)) {
				const auto& path = entry.path();
				if (std::filesystem::is_regular_file(path) == false) {
					continue;
				}

				auto extensionType = FileHelper::toFileExtension(FileHelper::fileExtensionString(path));
				if (extensionType != FileHelper::FileFormat::INVALID) {
					_filePathList.emplace_back(path);
				}
				else if (std::filesystem::is_directory(path))
					dirQueue.push(path);
			}
			dirQueue.pop();
		}

		for (const std::filesystem::path& p : _filePathList) {
			ConsoleLog::info(p.string());
		}
	}
	std::string_view getClassName() const {
		return outputFileName.substr(0 , outputFileName.find('.'));
	}
	void generateFile() const {
		/*
		namespace WebResources{
			static constexpr int file1_txt = 0;
			static constexpr int file2_css = 1;
			static constexpr int file3_js = 2;
			static constexpr int file4_html = 3;
			static constexpr int file5 = 4;
			static constexpr int file6 = 5;
			static constexpr int file7 = 6;
		}
		*/

		std::ofstream file(outputFileName);
		file << "namespace " << getClassName() << "{\n";
		for (const auto& path : _filePathList) {
			file << "static constexpr int ";
		}

		file << "}\n";
		file.close();
	}
private:
	std::string outputFileName;
	std::filesystem::path outputPath;
	std::filesystem::path projectDir;
	//the relative path list to the requested files( .html , .js  , .css). In this list , every nProjectFiles , you jump to the same file
	//but different extension
	std::vector<std::filesystem::path> _filePathList;
	
};
