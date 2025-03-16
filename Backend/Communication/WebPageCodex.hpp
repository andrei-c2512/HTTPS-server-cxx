#pragma once
#include "HttpCommon.hpp"
#include "WebComponent.hpp"
#include "FileHelper.hpp"
#include "WebLogisticsHandler.hpp"


//this class scans a folder with all of the web page files
//it then creates a separate folders of the same web page files but with different compressions
namespace WebDelivery {
	class PageCodex {
	public:
		//needs the path to where it can create folders to store stuff and a folder of the original stuff
		PageCodex(const std::string& storagePath , const std::string& webFolder)
			:storageDir(storagePath) , projectDir(webFolder) , handler(storagePath , webFolder)
		{
			assert(validDir(storageDir));
			assert(validDir(projectDir));
		}
		//returns empty string if not found
		std::string getPage(const std::string& fileName, FileHelper::FileFormat format) {
			return "";
		}
	private:
		static bool validDir(const std::string_view path) {
			return std::filesystem::exists(path) && std::filesystem::is_directory(path);
		}

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
