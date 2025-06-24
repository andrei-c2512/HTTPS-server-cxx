#include "Thumos/Web/WebPageCodex.hpp"


namespace thm::web{
        PageCodex::PageCodex(const std::string& storagePath , const std::string& webFolder)
                :storageDir(storagePath) , projectDir(webFolder) , handler(storagePath , webFolder)
        {
                assert(validDir(storageDir));
                assert(validDir(projectDir));
        }
        //returns empty string if not found
        std::string PageCodex::getPage(const std::string& fileName, file::FileFormat format) {
                return "";
        }
        bool PageCodex::validDir(const std::string_view path) {
                return std::filesystem::exists(path) && std::filesystem::is_directory(path);
        }
}
