#ifndef RCRD_FORMAT_HPP
#define RCRD_FORMAT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <assert.h>

#include "FileHandler.hpp"
#include "FileErrorHandler.hpp"

namespace RCRD {
	enum CardTypes {
		Poker,
		Tarot,
		Square,
		Mini
	};

	enum ElementFlags {

	};

	enum ElementTypes {
		Font,
		Image,
		Color,
		Text,
		Custom
	};

	static sf::Vector2f Formats[4] = {
		sf::Vector2f(2.5, 3.5),
		sf::Vector2f(2.75, 4.75),
		sf::Vector2f(2.5, 2.5),
		sf::Vector2f(1.65, 2.5)
	};

	struct Version {
		int major;
		int minor;
		int revision;
	};

	struct Timestamp {
		int day;
		int month;
		int year;
	};

	struct Header {
		std::string name;
		std::string author;
		Version version;
		Timestamp releaseDate;
		Timestamp lastMod;
	};

	struct ReferenceTable {
		std::vector<std::string> dataTable;
		int fonts[2];
		int colors[2];
		int images[2];
	};

	struct MainData {

	};
}

using namespace FileHandler;
using namespace RCRD;

class RCRDFile {
public:
	RCRDFile(FileErrorHandler errorHandler, std::string path);
	RCRDFile(FileErrorHandler errorHandler, std::string path, CardTypes size, std::string name, std::string author);

	bool LoadFromFile();
	bool WriteToFile();

	void SetVersion(const int maj, const int min, const int rev);
	void SetReleaseDate(const int d, const int m, const int y);
	void SetModDate(const int d, const int m, const int y);
	void SetName(const std::string name);
	void SetAuthor(const std::string author);

	bool AddElement(const std::string data, const ElementTypes type);

	bool IsGood();

private:
	bool m_loadLock = false, m_loaded = false;
	sf::Vector2f m_dimensions;
	std::string m_path;
	FileErrorHandler* m_errorHandler;

	Header m_header;
	ReferenceTable m_referenceTable;
	MainData m_mainData;

	void loadLockCheck();
};

#endif