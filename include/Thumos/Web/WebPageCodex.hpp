#pragma once
#include "Thumos/Web/WebLogisticsHandler.hpp"
#include "Thumos/Web/WebComponent.hpp"

//this class scans a folder with all of the web page files
//it then creates a separate folders of the same web page files but with different compressions
namespace thm::web{
        using namespace util;
	class PageCodex {
	public:
		//needs the path to where it can create folders to store stuff and a folder of the original stuff
		PageCodex(const std::string& storagePath , const std::string& webFolder);
		//returns empty string if not found
		std::string getPage(const std::string& fileName, file::FileFormat format);
	private:
		static bool validDir(const std::string_view path);
		//I need to think of a way to map a file name to a specific path. Ofc I could use maps but that would be MID
		//maybe I can generate code?
		//hmm
		
		/*
			Obiectivul ar fi urmatorul , la compile time , sa asocieze fiecarei apel a unei pagini 
			
		*/
	private:
		std::string storageDir;	
		std::string projectDir;
		//the relative path list to the requested files( .html , .js  , .css). In this list , every nProjectFiles , you jump to the same file
		//but different extension
		std::vector<std::filesystem::path> filePathList;
		//the relative path list to the requested resource files( .png , .gif , .mp4 etc)
		std::vector<std::filesystem::path> resourcePathList;
		size_t nProjectFiles = 0;
		LogisticsHandler handler;
	};
}
