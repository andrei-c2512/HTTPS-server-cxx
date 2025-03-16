#include "Common.hpp"
#include "ConsoleLog.hpp"
#include "FileHelper.hpp"
#include "DataCompressor.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"


namespace WebDelivery {
	class LogisticsHandler {
	public:
		LogisticsHandler(const std::string& storagePath0, const std::string& webFolder0)
			: storageDir(storagePath0) , projectDir(webFolder0)
		{
			makeDirectories();
			capturePaths();
			compressProject();
		}


		//this preprocessor shi is temporary
#if WEBPROJ_CLEANUP_ENABLED 
		~LogisticsHandler() {
			cleanUp();
		}
#else
		~LogisticsHandler() = default;
#endif

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

		//create the folders for the supported compression algorhitms
		void makeDirectories() const noexcept {
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

		void cleanUp() noexcept {
			for (const auto& entry : std::filesystem::directory_iterator(storageDir)) {
				const auto& path = entry.path();
				if (std::filesystem::remove_all(entry) == true) {
					ConsoleLog::info("Deleted directory");
				}
			}
		}

		void compressProject() {
			for (const auto& filePath : _filePathList) {
				FileReader reader(filePath.string());
				std::string data = reader.readFile();

				for (int32_t i = 0; i < (int32_t)FileHelper::CompressionType::COUNT; i++) {
					compressor.init(data, (FileHelper::CompressionType)i);
					auto compressedData = compressor.compress();
					std::filesystem::path newPath = storageDir;
					newPath = newPath / FileHelper::compressionNameArr.copyAt(i);

					FileWriter writer(newPath / filePath.filename());
					writer.writeToFile(compressedData);
				}
			}
		}
		const std::vector<std::filesystem::path>& filePathList() const noexcept {
			return _filePathList;
		}
	private:
		std::string storageDir;
		std::string projectDir;
		std::vector<std::filesystem::path> _filePathList;
		DataCompressor compressor;
	};
}