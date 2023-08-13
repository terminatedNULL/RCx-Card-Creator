#ifndef FILE_ERROR_HANDLER_HPP
#define FILE_ERROR_HANDLER_HPP

#include "FileHandler.hpp"

using namespace FileHandler;

class FileErrorHandler {
public:
	FileErrorHandler();
	~FileErrorHandler();

	Error& CreateError(ErrorType t, ErrorLevel l, std::string msg, std::string detail);
	void SetError(Error& e);
	Error& GetError();

private:
	Error* currError;

	void handleError();
};

#endif