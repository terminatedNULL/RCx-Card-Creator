#include "FileErrorHandler.hpp"

FileErrorHandler::FileErrorHandler() {
	currError = new Error;
}

FileErrorHandler::~FileErrorHandler() {
	delete currError;
}

Error& FileErrorHandler::CreateError(ErrorType t, ErrorLevel l, std::string msg, std::string detail) {
	Error* err = new Error{ t, l, msg + detail };
	return *err;
}

void FileErrorHandler::SetError(Error& e) { 
	currError = &e; handleError(); 
}

Error& FileErrorHandler::GetError() {
	return *currError;
}

void FileErrorHandler::handleError() {
	switch (currError->level) {
	case ErrorLevel::None:
		//System
		break;
	case ErrorLevel::Advisory:
		break;
	case ErrorLevel::Warning:
		break;
	case ErrorLevel::Failure:
		break;
	}
}