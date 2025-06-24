#pragma once
#include "Utility/Utility.hpp"

//vim test
//this is a file that generates another file with a class where each member has the name
//of a frontend file
class AssetHelper{
public:
        AssetHelper() = default;
	AssetHelper(std::filesystem::path webFolderPath  , std::filesystem::path outputPath0 , std::string generatedFileName = "WebResource.hpp");
	void capturePaths();
	std::string_view getClassName() const;
	void generateFile() const;
private:
	std::string outputFileName;
	std::filesystem::path outputPath;
	std::filesystem::path projectDir;
	//the relative path list to the requested files( .html , .js  , .css). In this list , every nProjectFiles , you jump to the same file
	//but different extension
	std::vector<std::filesystem::path> _filePathList;
	
};
