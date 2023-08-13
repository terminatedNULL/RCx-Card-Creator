#ifndef FILE_WINDOW_HPP
#define FILE_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <string>
#include <vector>

#include "RCxUI.hpp"
#include "FileHandler.hpp"

class FileWindow {
public:
	enum OpenMode {
		SelectFile = 0,
		SelectFiles,
		SelectFolder,
		SelectFolders,
		SaveFile
	};

	FileWindow(OpenMode mode);

	void Open(sf::RenderWindow& wind, std::string backPath);
	void Close();
	bool IsActive();

private:
	OpenMode m_mode;
	int m_screenW, screenH;
	int m_currentPage = 0;
	bool m_fileList = false, m_noFiles = false;
	bool m_active = false, m_fileSelected = false;
	bool m_pageButtons[2] = { false, false };
	std::string m_filter = ".";
	std::string m_title, m_back;

	char dirStr[256];
	std::vector <std::vector<std::string>> m_dirPages = { };

	std::vector <std::vector<std::string>> listDirFiles(std::string dir, std::string filter);
};

#endif