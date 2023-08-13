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
	Button(float x, float y, float width, float height, int radius, sf::String text, sf::Font& font, int size, bool radio = false);

	void SetColors(sf::Color normalColor, sf::Color hoverColor, sf::Color clickColor);
	void SetTextColors(sf::Color normalColor, sf::Color hoverColor, sf::Color clickColor);
	void SetCurrentTextColor(sf::Color col);
	void SetOutline(int width, sf::Color col);
	void SetTextOutline(int width, sf::Color col);
	void SetState(int state);
	void SetText(std::string text);
	void SetPosition(int x, int y);
	void SetPagePos(sf::Vector2i pos);
	void SetRadio(bool state);
	void SetRadioState(bool state);
	void SetActive(bool state);

	std::string GetText();
	int GetState();
	sf::Vector2f GetPosition();
	sf::Vector2i GetPagePosition();
	bool GetRadioState();
	bool GetActive();

	void Draw(sf::RenderWindow& wind);
	void Hover(sf::RenderWindow& wind);
	bool Click(sf::Event event, sf::RenderWindow& wind);
	void Release(sf::Event event, sf::RenderWindow& wind);
	
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

	void checkTextSize(sf::Text& text, sf::Vector2f container);
};

#endif