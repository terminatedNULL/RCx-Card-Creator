#ifndef FILE_ERROR_HANDLER_HPP
#define FILE_ERROR_HANDLER_HPP

#include "FileHandler.hpp"

using namespace FileHandler;

class FileErrorHandler {
public:
	FileErrorHandler();
	~FileErrorHandler();

	static Error& CreateError(const ErrorType type, const ErrorLevel level, const std::string msg, const std::string detail);
	void SetError(Error& e);
	Error& GetError() const;

private:
	Error* m_currError;

	void handleError() const;
};

#endif