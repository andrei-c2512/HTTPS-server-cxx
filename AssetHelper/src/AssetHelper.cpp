#include "AssetHelper/AssetHelper.hpp"


AssetHelper::AssetHelper(std::filesystem::path webFolderPath  , std::filesystem::path outputPath0 , std::string generatedFileName)
        :projectDir(webFolderPath) , outputFileName(generatedFileName) , outputPath(outputPath0)
{}
void AssetHelper::capturePaths() {
        std::queue<std::filesystem::path> dirQueue;
        dirQueue.emplace(projectDir);

        while (dirQueue.empty() == false) {
                const auto& dir = dirQueue.front();
                for (const auto& entry : std::filesystem::directory_iterator(dir)) {
                        const auto& path = entry.path();
                        if (std::filesystem::is_regular_file(path) == false) {
                                continue;
                        }

                        auto extensionType = util::file::toFileExtension(util::file::fileExtensionString(path));
                        if (extensionType != util::file::FileFormat::INVALID) {
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
std::string_view AssetHelper::getClassName() const {
        // FIX THIS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        return outputFileName.substr(0 , outputFileName.find('.'));
}
void AssetHelper::generateFile() const {
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
