#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <Windows.h>
#include "dirEnt.h"

namespace FileHandler {
	enum ErrorLevel {
		None,
		Advisory,
		Warning,
		Failure
	};

	enum ErrorType {
		NoError,
		DuplicateValue,
		OpenFailure
	};

	static std::string ErrorMessages[3] = {
		"No Error",
		"Duplicate value found during function runtime: ",
		"Failed to open file: "
	};

	struct Error {
		ErrorType type = ErrorType::NoError;
		ErrorLevel level = ErrorLevel::None;
		std::string message = ErrorMessages[ErrorType::NoError];
	};

	std::vector<std::string> OpenFileFromPath(const std::string dirPath);
	std::vector<std::string> FileContentsToVector(const std::string fileContents);
	std::vector<std::string> FilesInDirectory(const std::string dirPath, const std::string filter);
	std::vector<std::string> SetFilter(const std::vector<std::string> inFiles, const std::string fileExt);
}

#endif