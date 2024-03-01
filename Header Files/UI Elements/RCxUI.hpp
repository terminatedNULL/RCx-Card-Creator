#ifndef RCX_UI_HPP
#define RCX_UI_HPP

#define NOMINMAX //Stop <Windows.h> from crumpling SFML

#include <string>

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include "SystemStyle.hpp"
#include "Button.hpp"
#include "CustomShapes.hpp"
#include "GradientRectangle.hpp"
#include "Line.hpp"
#include "Picture.hpp"
#include "Textbox.hpp"
#include "SystemStyle.hpp"

namespace RCxUI {
    const sf::Color BACKGROUND = Colors[SysPalette::Background];
    const sf::Color FOREGROUND = Colors[SysPalette::Foreground];
    const sf::Color TOP_GRADIENT = Colors[SysPalette::TopGradient];
    const sf::Color BOTTOM_GRADIENT = Colors[SysPalette::BottomGradient];
    const sf::Color PRIMARY_TEXT = Colors[SysPalette::PrimaryText];
    const sf::Color SECONDARY_TEXT = Colors[SysPalette::SecondaryText];
    const sf::Color ACCENT = Colors[SysPalette::AccentColor];

    const ImVec4 IM_BACKGROUND = ImColors[SysPalette::Background];
    const ImVec4 IM_FOREGROUND = ImColors[SysPalette::Foreground];
    const ImVec4 IM_TOP_GRADIENT = ImColors[SysPalette::TopGradient];
    const ImVec4 IM_BOTTOM_GRADIENT = ImColors[SysPalette::BottomGradient];
    const ImVec4 IM_PRIMARY_TEXT = ImColors[SysPalette::PrimaryText];
    const ImVec4 IM_SECONDARY_TEXT = ImColors[SysPalette::SecondaryText];
    const ImVec4 IM_ACCENT = ImColors[SysPalette::AccentColor];

    const unsigned int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
    const unsigned int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

    //Used for most UI buttons
    inline void buttonBareBones(Button& b) {
        b.SetColors(sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent);
        b.SetTextColors(ACCENT, SECONDARY_TEXT, PRIMARY_TEXT);
    }

    //Basic window background used by all windows - 1/3 of screen width
    inline void DrawBackgroundTitle(sf::RenderWindow& wind, const std::string& title, const sf::Font& font) {
        sf::RectangleShape backgroundObj(sf::Vector2f(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 1.5));
        backgroundObj.setPosition(sf::Vector2f(
            (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 3) / 2,
            (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 1.5) / 2)
        );
        backgroundObj.setFillColor(sf::Color(40, 40, 40));
        backgroundObj.setOutlineThickness(3);
        backgroundObj.setOutlineColor(sf::Color(64, 64, 64));

        sf::Text titleObj(title, font, 20);
        titleObj.setPosition(sf::Vector2f(
            (SCREEN_WIDTH / 2) - (SCREEN_WIDTH / 3) / 2 + 10 + (SCREEN_WIDTH / 6 - titleObj.getGlobalBounds().width / 2),
            (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 1.5) / 2 + 3
        ));
        titleObj.setFillColor(sf::Color(7, 132, 181));
        titleObj.setOutlineThickness(1);
        titleObj.setOutlineColor(sf::Color::Black);

        wind.draw(backgroundObj);
        wind.draw(titleObj);
    }
}

#endif