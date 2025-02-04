#pragma once
#include "HttpCommon.hpp"
#include "WebComponent.hpp"
#include "FileHelper.hpp"

#define CLEAN_UP_ENABLED true

//this class scans a folder with all of the web page files
//it then creates a separate folders of the same web page files but with different compressions
namespace WebDelivery {
	class PageCodex {
	public:
		//needs the path to where it can create folders to store stuff and a folder of the original stuff
		PageCodex(const std::string& storagePath , const std::string& webFolder)
			:storageDir(storagePath) , projectDir(webFolder)
		{
			assert(validDir(storageDir));
			assert(validDir(projectDir));
			makeDirectories();
			capturePaths();
		}

		//this preprocessor shi is temporary
#if CLEAN_UP_ENABLED 
		~PageCodex() {
			cleanUp();
		}
#else
		~PageCodex() = default;
#endif

		//create the folders for the supported compression algorhitms
		void makeDirectories() const noexcept{
			std::filesystem::path storageFolderPath = storageDir;
			for (const std::string_view folder : FileHelper::compressionNameArr.arr) {
				std::filesystem::path folderPath = storageFolderPath.append(std::string(folder.data()));
				storageFolderPath = storageDir;

				ConsoleLog::info(folderPath.string());
				if (!std::filesystem::exists(folderPath))
				{
					std::filesystem::create_directory(folderPath);
					ConsoleLog::info("Created directory <" + std::string(folder.data()) + ">");
				}
			}
			ConsoleLog::info("Made/verrified necessary directories for web delivery");
		}
		//initialises the project paths
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
						filePathList.emplace_back(path);
					}
					else if (std::filesystem::is_directory(path))
						dirQueue.push(path);
				}
				dirQueue.pop();
			}
			nProjectFiles = filePathList.size();
		
			for (const std::filesystem::path& p : filePathList) {
				ConsoleLog::info(p.string());
			}
		}
		//returns empty string if not found
		std::string getPage(const std::string& fileName, FileHelper::FileFormat format) {
			return "";
		}
	private:
		static bool validDir(const std::string_view path) {
			return std::filesystem::exists(path) && std::filesystem::is_directory(path);
		}
		void cleanUp() noexcept {
			for (const auto& entry : std::filesystem::directory_iterator(storageDir)) {
				const auto& path = entry.path();
				if (std::filesystem::remove_all(entry) == true) {
					ConsoleLog::info("Deleted directory");
				}
			}
		}
	private:
		std::string storageDir;	
		std::string projectDir;
		//the relative path list to the requested files( .html , .js  , .css). In this list , every nProjectFiles , you jump to the same file
		//but different extension
		std::vector<std::filesystem::path> filePathList;
		//the relative path list to the requested resource files( .png , .gif , .mp4 etc)
		std::vector<std::filesystem::path> resourcePathList;
		size_t nProjectFiles = 0;
	};
}
