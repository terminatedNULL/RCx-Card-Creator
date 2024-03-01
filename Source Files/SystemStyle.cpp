#include "SystemStyle.hpp"

namespace fs = std::experimental::filesystem;

SystemStyleHandler::SystemStyleHandler() {

}

void SystemStyleHandler::InitializeFonts() {
	const fs::path currentPath = fs::current_path();
	const fs::path fontFolderPath = currentPath / fs::path("Assets") / fs::path("Fonts");

	for (std::string& s : SysFontPaths) {
		sf::Font f;
		fs::path fontFilePath = fontFolderPath / fs::path(s);
		f.loadFromFile(fontFilePath.u8string());
		Fonts.push_back(f);
	}
}

sf::Color SystemStyleHandler::Alpha(sf::Color col, const float alpha) {
	return { col.r, col.g, col.b, static_cast<sf::Uint8>(alpha) };
}

ImVec4 SystemStyleHandler::ImAlpha(const ImVec4 col, const float alpha) {
	return { col.x, col.y, col.z, alpha };
}