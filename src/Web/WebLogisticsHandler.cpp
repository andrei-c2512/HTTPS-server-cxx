#include "Thumos/Web/WebLogisticsHandler.hpp"

namespace thm::web{
        LogisticsHandler::LogisticsHandler(const std::string& storagePath0, const std::string& webFolder0)
                : storageDir(storagePath0) , projectDir(webFolder0)
        {
                makeDirectories();
                capturePaths();
                compressProject();
        }
        //initialises the project paths
        void LogisticsHandler::capturePaths() {
                std::queue<std::filesystem::path> dirQueue;
                dirQueue.emplace(projectDir);

                while (dirQueue.empty() == false) {
                        const auto& dir = dirQueue.front();
                        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
                                const auto& path = entry.path();
                                if (std::filesystem::is_regular_file(path) == false) {
                                        continue;
                                }

                                auto extensionType = file::toFileExtension(file::fileExtensionString(path));
                                if (extensionType != file::FileFormat::INVALID) {
                                        _filePathList.emplace_back(path);
                                }
                                else if (std::filesystem::is_directory(path))
                                        dirQueue.push(path);
                        }
                        dirQueue.pop();
                }

                for (const std::filesystem::path& p : _filePathList) {
                        util::log::info(p.string());
                }
        }

        //create the folders for the supported compression algorhitms
        void LogisticsHandler::makeDirectories() const noexcept {
                std::filesystem::path storageFolderPath = storageDir;
                for (const std::string_view folder : file::compressionNameArr.arr) {
                        std::filesystem::path folderPath = storageFolderPath.append(std::string(folder.data()));
                        storageFolderPath = storageDir;

                        util::log::info(folderPath.string());
                        if (!std::filesystem::exists(folderPath))
                        {
                                std::filesystem::create_directory(folderPath);
                                util::log::info("Created directory <" + std::string(folder.data()) + ">");
                        }
                }
                util::log::info("Made/verrified necessary directories for web delivery");
        }

        void LogisticsHandler::cleanUp() noexcept {
                for (const auto& entry : std::filesystem::directory_iterator(storageDir)) {
                        const auto& path = entry.path();
                        if (std::filesystem::remove_all(entry) == true) {
                                util::log::info("Deleted directory");
                        }
                }
        }

        void LogisticsHandler::compressProject() {
                for (const auto& filePath : _filePathList) {
                        FileReader reader(filePath.string());
                        std::string data = reader.readFile();

                        for (int32_t i = 0; i < (int32_t)file::CompressionType::COUNT; i++) {
                                compressor.init(data, (file::CompressionType)i);
                                auto compressedData = compressor.compress();
                                std::filesystem::path newPath = storageDir;
                                newPath = newPath / file::compressionNameArr.copyAt(i);

                                FileWriter writer(newPath / filePath.filename());
                                writer.writeToFile(compressedData);
                        }
                }
        }
        const std::vector<std::filesystem::path>& LogisticsHandler::filePathList() const noexcept {
                return _filePathList;
        }
}
