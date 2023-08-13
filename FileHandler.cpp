#include "FileHandler.hpp"

std::vector<std::string> FileHandler::OpenFileFromPath(std::string dirPath) {
	std::ifstream openFile;
	std::vector<std::string> result;

	openFile.open(dirPath);
	if (openFile.is_open()) {
		std::string line;
		while (!openFile.eof()) {
			std::getline(openFile, line);
			result.push_back(line);
		}
	}

	return result;
}

std::vector<std::string> FileHandler::FileContentsToVector(std::string fileContents) {
	std::vector<std::string> contents;
	std::stringstream stream(fileContents);
	std::string line;

	while (std::getline(stream, line, '\n')) { contents.push_back(line); }

	return contents;
}

std::vector<std::string> FileHandler::FilesInDirectory(std::string dirPath, std::string filter) {
	std::vector<std::string> fileList;
	std::string compatPath = dirPath;

	size_t pos = 0;
	while ((pos = compatPath.find("\\", pos)) != std::string::npos) {
		compatPath.replace(pos, std::string("\\").length(), "\\\\");
		pos += std::string("\\\\").length();
	}

	DIR* pDIR;
	struct dirent* entry;
	if (pDIR = opendir(compatPath.c_str())) {
		while (entry = readdir(pDIR)) {
			if (strcmp(entry->d_name, filter.c_str()) != 0 && strcmp(entry->d_name, "..") != 0) {
				fileList.push_back(entry->d_name);
			}
		}
		closedir(pDIR);
	}

	return fileList;
}

std::vector<std::string> FileHandler::SetFilter(std::vector<std::string> inFiles, std::string fileExt) {
	for (int i = 0; i < inFiles.size(); i++) {
		if (inFiles[i].find(fileExt) == std::string::npos) {
			inFiles.erase(inFiles.begin() + i);
		}
	}
	return inFiles;
}