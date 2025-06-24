#include "Thumos/Web/DataCompressor.hpp"


namespace thm::web{
        using namespace util;
	class LogisticsHandler {
	public:
		LogisticsHandler(const std::string& storagePath0, const std::string& webFolder0);
		//this preprocessor shi is temporary
#if WEBPROJ_CLEANUP_ENABLED 
                ~LogisticsHandler() {
                        cleanUp();
                }
#else
		~LogisticsHandler() = default;
#endif

		//initialises the project paths
		void capturePaths();
		//create the folders for the supported compression algorhitms
		void makeDirectories() const noexcept;
		void cleanUp() noexcept;
		void compressProject();
		const std::vector<std::filesystem::path>& filePathList() const noexcept;
	private:
		std::string storageDir;
		std::string projectDir;
		std::vector<std::filesystem::path> _filePathList;
		DataCompressor compressor;
	};
}
