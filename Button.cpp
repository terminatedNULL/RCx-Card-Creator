#include "Button.hpp"

#include <functional>
#include "CustomShapes.hpp"
#include "TextHelp.hpp"

using namespace TextTools;

Button::Button(float x, float y, float width, float height, int radius, sf::String text, sf::Font& font, int size, bool radio) : m_font(font), m_state(0) {
	m_buttonRect = RoundedRectangle(0, 0, width, height, radius, sf::Color::White);
	m_buttonRect.move((int)x, (int)y);

	m_size = sf::Vector2f(width, height);
	m_pos = sf::Vector2f(x, y);
	m_radio.first = radio;

	m_text = sf::Text(text, font, size);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(centerText(x, y, m_text, font, m_size.x, m_size.y));
	m_isActive = true;
}

//=============================================================================================
// SET FUNCTIONS
//=============================================================================================
void Button::SetColors(sf::Color normalColor, sf::Color hoverColor, sf::Color clickColor) {
	m_buttonRect.setFillColor(normalColor);
	m_color[0] = normalColor;
	m_color[1] = hoverColor;
	m_color[2] = clickColor;
}

void Button::SetTextColors(sf::Color normalColor, sf::Color hoverColor, sf::Color clickColor) {
	m_text.setFillColor(normalColor);
	m_textColor[0] = normalColor;
	m_textColor[1] = hoverColor;
	m_textColor[2] = clickColor;
}

void Button::SetCurrentTextColor(sf::Color col) {
	m_text.setFillColor(col);
	m_textColor[m_state] = col;
}

void Button::SetOutline(int width, sf::Color col) {
	m_buttonRect.setOutlineThickness(width);
	m_buttonRect.setOutlineColor(col);
}

void Button::SetTextOutline(int width, sf::Color col) {
	m_text.setOutlineColor(col);
	m_text.setOutlineThickness(width);
}

void Button::SetState(int state) {
	if (m_state == state || !m_isActive) { return; }
	m_state = state;
	m_buttonRect.setFillColor(m_color[m_state]);
	m_text.setFillColor(m_textColor[m_state]);
}

void Button::SetText(std::string text) {
	m_text.setString(text);
	m_text.setPosition(
		centerText(m_pos.x, m_pos.y, m_text, m_font, m_size.x, m_size.y)
	);
}

void Button::SetPosition(int x, int y) {
	m_pos = sf::Vector2f(x, y);
	m_buttonRect.move((int)x, (int)y);
	m_text.setPosition(centerText(x, y, m_text, m_font, m_size.x, m_size.y));
}

void Button::SetPagePos(sf::Vector2i pos) { 
	m_pagePos = pos; 
}

void Button::SetRadio(bool state) { 
	m_radio.first = state; 
}

void Button::SetRadioState(bool state) {
	m_radio.second = state;
}

void Button::SetActive(bool state) {
	m_isActive = state;
	if (!state) {
		m_text.setFillColor(sf::Color(115, 115, 115));
	}
	else {
		m_text.setFillColor(m_textColor[m_state]);
	}
}

//=============================================================================================
// GET FUNCTIONS
//=============================================================================================

std::string Button::GetText() {
	return m_text.getString();
}

int Button::GetState() {
	return m_state; 
}

sf::Vector2f Button::GetPosition() {
	return m_pos; 
}

sf::Vector2i Button::GetPagePosition() {
	return m_pagePos; 
}

bool Button::GetRadioState() {
	return (m_radio.second); 
}

bool Button::GetActive() {
	return m_isActive; 
}

//=============================================================================================
// BASE FUNCTIONS
//=============================================================================================

void Button::Draw(sf::RenderWindow& wind) {
	wind.draw(m_buttonRect);
	wind.draw(m_text);
}

void Button::Hover(sf::RenderWindow& wind) {
	if (BoundsCheck(m_pos, m_size, wind) && !(m_radio.first && m_radio.second)) {
		if (m_state == 0) { SetState(1); }
	}
	else if (!(m_radio.first && m_radio.second)) {
		SetState(0);
	}
}

bool Button::Click(sf::Event event, sf::RenderWindow& wind) {
	if (BoundsCheck(m_pos, m_size, wind) && m_isActive) {
		if (m_radio.first) { m_radio.second = !m_radio.second; }
		SetState(2);
		return true;
	}
	return false;
}

void Button::Release(sf::Event event, sf::RenderWindow& wind) {
	if (BoundsCheck(m_pos, m_size, wind)) {
		SetState(1);
	}
}

//=============================================================================================
// INTERNAL FUNCTIONS
//=============================================================================================

void Button::checkTextSize(sf::Text& text, sf::Vector2f container) {
	if (TextSize(text.getString(), m_font, text.getCharacterSize()).x > container.x) {

	}
}