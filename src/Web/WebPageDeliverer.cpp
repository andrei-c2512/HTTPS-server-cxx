#include "Thumos/Web/WebPageDeliverer.hpp"

namespace thm::web{
        PageDeliverer::PageDeliverer(const std::string& storagePath , const std::string& webFolderPath )
                :codex(storagePath , webFolderPath)
        {}
        std::string PageDeliverer::getFile(std::string_view fileName, std::vector<file::CompressionType> supported) {
                file.open(fileName.data());

                if (file.is_open()) {
                        util::log::info("Sucessfully opened the file");
                        file.seekg(std::ios::end);
                        size_t fileSize = file.tellg();
                        file.seekg(std::ios::beg);

                        std::string fileData(fileSize, '\0');
                        file.read(fileData.data(), fileSize);

                        return fileData;


                        file.close();
                }
                else {
                        util::log::error("Could not open the file");
                        return "";
                }
        }
}
