#include "SystemStyle.hpp"

namespace fs = std::experimental::filesystem;

SystemStyleHandler::SystemStyleHandler() {

}

void SystemStyleHandler::InitializeFonts() {
	fs::path currentPath = fs::current_path();
	fs::path fontFolderPath = currentPath / fs::path("Assets") / fs::path("Fonts");

	for (std::string s : SysFontPaths) {
		sf::Font f;
		fs::path fontFilePath = fontFolderPath / fs::path(s);
		f.loadFromFile(fontFilePath.u8string());
		Fonts.push_back(f);
	}
}

sf::Color SystemStyleHandler::Alpha(sf::Color col, float alpha) {
	return sf::Color(col.r, col.g, col.b, alpha);
}

ImVec4 SystemStyleHandler::ImAlpha(ImVec4 col, float alpha) {
	return ImVec4(col.x, col.y, col.z, alpha);
}