#include "FileWindow.hpp"

const int FILE_WIND_BUTTONS = 20;

using namespace RCxUI;

FileWindow::FileWindow(OpenMode mode)  : m_mode(mode) {
	switch (mode) {
	case SelectFile:
		m_title = "Select File";
		break;
	case SelectFiles:
		m_title = "Select Files";
		break;
	case SelectFolder:
		m_title = "Select Folder";
		break;
	case SelectFolders:
		m_title = "Select Folders";
		break;
	case SaveFile:
		m_title = "Select Save Location";
		break;
	}
}

void FileWindow::Open(sf::RenderWindow& wind, std::string backPath) {
	m_back = backPath;
	m_active = true;
	sf::Image backgroundImg;
	sf::Texture backgroundTex;
	sf::Sprite background;	
	backgroundImg.loadFromFile(m_back);
	backgroundTex.loadFromImage(backgroundImg);
	background.setTexture(backgroundTex);

	while (m_active) {
		sf::Clock deltaClock;
		sf::Event event;

		while (wind.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
		}

		ImGui::SFML::Update(wind, deltaClock.restart());

		wind.clear();

		ImGui::SetNextWindowSize(ImVec2(sf::VideoMode::getDesktopMode().width / 3, sf::VideoMode::getDesktopMode().height / 2));
		ImGui::SetNextWindowPos(ImVec2((SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 3) / 2, (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 1.5) / 2));
		ImGui::SetNextWindowBgAlpha(0);

		ImGui::Begin(m_title.c_str(), nullptr,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar
		);

		//Draw window elements
		if (ImGui::Button("LOAD", ImVec2(100, 50))) {
			m_fileList = true;
			m_dirPages = listDirFiles((std::string)dirStr, m_filter);

			if (m_dirPages.size() == 0) { 
				m_noFiles = true; 
			} else { 
				m_noFiles = false; 
			}
		}

		if (!m_noFiles) {
			//display no files text
		}

		if (m_fileList && !m_noFiles) {
			//display file list buttons
		}

		ImGui::SameLine();
		ImGui::InputText("##directoryBox", dirStr, 256);
		ImGui::End();

		wind.draw(background);

		ImGui::SFML::Render(wind);
		wind.display();
	}
}

void FileWindow::Close() {
	m_active = false;
}

bool FileWindow::IsActive() {
	return m_active;
}

std::vector<std::vector<std::string>> FileWindow::listDirFiles(std::string dir, std::string filter) {
	std::vector<std::string> dirFiles = FileHandler::FilesInDirectory(dir, filter);
	std::vector<std::vector<std::string>> returnVec = { };
	int dirLength = dirFiles.size(), genLength;
	if (dirLength == 0) { return returnVec; }

	for (int i = 0; i < ceil((double)dirLength / (double)FILE_WIND_BUTTONS); i++) {
		if (dirLength - FILE_WIND_BUTTONS * i > FILE_WIND_BUTTONS) {
			genLength = FILE_WIND_BUTTONS; 
		} else { 
			genLength = dirLength - FILE_WIND_BUTTONS * i; 
		}

		returnVec.push_back({});
		for (int j = 0; j < genLength; j++) {
			returnVec[i].push_back(dirFiles[FILE_WIND_BUTTONS * i + j]);
		}
	}

	return returnVec;
}