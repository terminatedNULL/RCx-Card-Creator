#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "CustomShapes.hpp"
#include "TextHelp.hpp"
#include "Interactable.hpp"

class Button : public Interactable {
public:
	Button(
		const int x, const int y, const int width, const int height,
		const int size, const int radius, const sf::String& text,
		sf::Font& font, const bool radio
	);

	void SetColors(const sf::Color normalColor, const sf::Color hoverColor, const sf::Color clickColor);
	void SetTextColors(const sf::Color normalColor, const sf::Color hoverColor, const sf::Color clickColor);
	void SetCurrentTextColor(const sf::Color col);
	void SetOutline(const int width, const sf::Color col);
	void SetTextOutline(const int width, const sf::Color col);
	void SetState(const int state);
	void SetText(const std::string text);
	void SetPosition(const int x, const int y);
	void SetPagePos(const sf::Vector2i pos);
	void SetRadio(const bool state);
	void SetRadioState(const bool state);
	void SetActive(const bool state);

	std::string GetText();
	int GetState();
	sf::Vector2f GetPosition();
	sf::Vector2i GetPagePosition();
	bool GetRadioState();
	bool GetActive();

	void Draw(sf::RenderWindow& wind);
	void Hover(sf::RenderWindow& wind);
	bool Click(const sf::Event event, sf::RenderWindow& wind);
	void Release(const sf::Event event, sf::RenderWindow& wind);
	
private:
	sf::ConvexShape m_buttonRect;

	sf::Text m_text;
	sf::Font m_font;

	sf::Color m_color[3] = {sf::Color::White, sf::Color::White , sf::Color::White};
	sf::Color m_textColor[3] = {sf::Color::Black, sf::Color::Black , sf::Color::Black};

	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Vector2i m_pagePos;

	int m_state; // 0 -> IDLE | 1 -> HOVER | 2 -> CLICK
	std::pair<bool, bool> m_radio; // Is radio | Is selected
	bool m_isActive;

	void checkTextSize(sf::Text& text, const sf::Vector2f container);
};

#endif