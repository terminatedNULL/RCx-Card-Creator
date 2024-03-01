#include "FileErrorHandler.hpp"

FileErrorHandler::FileErrorHandler() {
	m_currError = new Error;
}

FileErrorHandler::~FileErrorHandler() {
	delete m_currError;
}

Error& FileErrorHandler::CreateError(ErrorType t, ErrorLevel l, std::string msg, std::string detail) {
	Error* err = new Error{ t, l, msg + detail };
	return *err;
}

void FileErrorHandler::SetError(Error& e) { 
	m_currError = &e; handleError(); 
}

Error& FileErrorHandler::GetError() const {
	return *m_currError;
}

void FileErrorHandler::handleError() const {
	switch (m_currError->level) {
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