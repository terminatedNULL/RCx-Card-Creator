#ifndef SYSTEM_STYLE_HPP
#define SYSTEM_STYLE_HPP

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <fstream>

#include "imgui.h"

	enum SysFonts {
		Regular,
		Two,
		Four,
		Eight,
		Hair,
		Thin,
		UltraLight,
		ExtraLight,
		Light,
		Book,
		Medium,
		SemiBold,
		Bold,
		ExtraBold,
		Heavy,
		Ultra,
		Italic,
		TwoItalic,
		FourItalic,
		EightItalic,
		HairItalic,
		ThinItalic,
		UltraLightItalic,
		ExtraLightItalic,
		LightItalic,
		BookItalic,
		MediumItalic,
		SemiBoldItalic,
		BoldItalic,
		ExtraBoldItalic,
		HeavyItalic,
		UltraItalic,
	};

	enum SysPallete {
		Background,
		Foreground,
		TopGradient,
		BottomGradient,
		PrimaryText,
		SecondaryText,
		AccentColor
	};

	static sf::Color Colors[7] = {
			sf::Color(18, 18, 18),
			sf::Color(24, 24, 24),
			sf::Color(64, 64, 64),
			sf::Color(40, 40, 40),
			sf::Color(255, 255, 255),
			sf::Color(179, 179, 179),
			sf::Color(7, 132, 181)
	};

	static ImVec4 ImColors[7] = {
			ImVec4(0.071f, 0.071f, 0.071f, 1.f),
			ImVec4(0.094f, 0.094f, 0.094f, 1.f),
			ImVec4(0.251f, 0.251f, 0.251f, 1.f),
			ImVec4(0.157f, 0.157f, 0.157f, 1.f),
			ImVec4(1.f, 1.f, 1.f, 1.f),
			ImVec4(0.702f, 0.702f, 0.702f, 1.f),
			ImVec4(0.027f, 0.518f, 0.71f, 1.f)
	};

class SystemStyleHandler {
public:
	SystemStyleHandler();

	void InitializeFonts();

	sf::Color Alpha(sf::Color col, float alpha);
	ImVec4 ImAlpha(ImVec4 col, float alpha);

	std::vector<sf::Font> Fonts;

private:
	std::string SysFontPaths[32] = {
		"FiraSans-Regular.ttf",
		"FiraSans-Two.ttf",
		"FiraSans-Four.ttf",
		"FiraSans-Eight.ttf",
		"FiraSans-Hair.ttf",
		"FiraSans-Thin.ttf",
		"FiraSans-UltraLight.ttf",
		"FiraSans-ExtraLight.ttf",
		"FiraSans-Light.ttf",
		"FiraSans-Book.ttf",
		"FiraSans-Medium.ttf",
		"FiraSans-SemiBold.ttf",
		"FiraSans-Bold.ttf",
		"FiraSans-ExtraBold.ttf",
		"FiraSans-Heavy.ttf",
		"FiraSans-Ultra.ttf",
		"FiraSans-Italic.ttf",
		"FiraSans-TwoItalic.ttf",
		"FiraSans-FourItalic.ttf",
		"FiraSans-EightItalic.ttf",
		"FiraSans-HairItalic.ttf",
		"FiraSans-ThinItalic.ttf",
		"FiraSans-UltraLightItalic.ttf",
		"FiraSans-ExtraLightItalic.ttf",
		"FiraSans-LightItalic.ttf",
		"FiraSans-BookItalic.ttf",
		"FiraSans-MediumItalic.ttf",
		"FiraSans-SemiBoldItalic.ttf",
		"FiraSans-BoldItalic.ttf",
		"FiraSans-ExtraBoldItalic.ttf",
		"FiraSans-HeavyItalic.ttf",
		"FiraSans-UltraItalic.ttf",
	};
};

#endif