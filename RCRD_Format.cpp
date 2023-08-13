#include "RCRD_Format.hpp"

RCRDFile::RCRDFile(FileErrorHandler errorHandler, std::string path)
	: m_path(path), m_errorHandler(&errorHandler), m_loadLock(true) { }

RCRDFile::RCRDFile(FileErrorHandler errorHandler, std::string path, CardTypes size, std::string name, std::string author) :
	m_path(path), m_dimensions(Formats[size]), m_errorHandler(&errorHandler)
{
	m_header.name = name;
	m_header.author = author;
}

bool RCRDFile::LoadFromFile() {
	std::ifstream file(m_path, std::ios::in | std::ios::binary);
	if (!file) { return false; }

	file.read((char*)&m_header, sizeof(Header));
	file.read((char*)&m_referenceTable, sizeof(ReferenceTable));
	file.read((char*)&m_mainData, sizeof(MainData));
	file.close();

	m_loaded = true;
	return true;
}

bool RCRDFile::WriteToFile() {
	std::ofstream file(m_path, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!file) { return false; }

	file.write((char*)&m_header, sizeof(Header));
	file.write((char*)&m_referenceTable, sizeof(ReferenceTable));
	file.write((char*)&m_mainData, sizeof(MainData));
	file.close();

	return true;
}

void RCRDFile::SetVersion(int maj, int min, int rev) {
	loadLockCheck();
	m_header.version.major = maj;
	m_header.version.minor = min;
	m_header.version.revision = rev;
}

void RCRDFile::SetReleaseDate(int d, int m, int y) {
	loadLockCheck();
	m_header.releaseDate.day = d;
	m_header.releaseDate.month = m;
	m_header.releaseDate.year = y;
}

void RCRDFile::SetModDate(int d, int m, int y) {
	loadLockCheck();
	m_header.lastMod.day = d;
	m_header.lastMod.month = m;
	m_header.lastMod.year = y;
}

//Note: A card's name and author are pre-set on creation - 
//		therefore these should really only be called by user interaction
void RCRDFile::SetName(std::string name) { 
	m_header.name = name; 
}

void RCRDFile::SetAuthor(std::string author) { 
	m_header.author = author;
}

bool RCRDFile::AddElement(std::string data, ElementTypes type) {
	for (std::string s : m_referenceTable.dataTable) {
		if (s == data) {
			m_errorHandler->SetError(
				m_errorHandler->CreateError(
					ErrorType::DuplicateValue,
					ErrorLevel::Warning,
					ErrorMessages[ErrorType::DuplicateValue],
					"AddElement()"
				)
			);
			return false;
		}
	}

	bool mod[] = { false, false, false };

	switch (type) {
	case ElementTypes::Font:
		m_referenceTable.dataTable.insert(
			m_referenceTable.dataTable.begin() + m_referenceTable.fonts[1],
			data
		);
		mod[ElementTypes::Image] = true;
		mod[ElementTypes::Color] = true;
		break;
	case ElementTypes::Image:
		m_referenceTable.dataTable.insert(
			m_referenceTable.dataTable.begin() + m_referenceTable.images[1],
			data
		);
		mod[ElementTypes::Font] = true;
		mod[ElementTypes::Color] = true;
		break;
	case ElementTypes::Color:
		m_referenceTable.dataTable.insert(
			m_referenceTable.dataTable.begin() + m_referenceTable.colors[1],
			data
		);
		mod[ElementTypes::Font] = true;
		mod[ElementTypes::Image] = true;
		break;
	}

	if (mod[0]) {
		m_referenceTable.fonts[0]++;
		m_referenceTable.fonts[1]++;
	}
	if (mod[1]) {
		m_referenceTable.colors[0]++;
		m_referenceTable.colors[1]++;
	}
	if (mod[2]) {
		m_referenceTable.images[0]++;
		m_referenceTable.images[1]++;
	}
	return true;
}

bool RCRDFile::IsGood() {
	return m_loaded; 
}

//Stop! You should not be touching an unloaded or uninstantiated file!
void RCRDFile::loadLockCheck() { assert(!m_loadLock && m_loaded); }