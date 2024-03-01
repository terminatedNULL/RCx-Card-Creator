#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <cassert>

#include "Interactable.hpp"
#include "TextHelp.hpp"

#define DELETE_K 8
#define ENTER 13
#define PASTE 22
#define ESCAPE 27

class Textbox : public Interactable {
public:
	Textbox(const float x, const float y, const int width, const int height, const std::string text);

	void BackgroundBorderDetails(const sf::Color bgCol, const sf::Color borderCol, const int borderWidth);
	void SetColor(const sf::Color col);
	void SetCharacterSize(const int cSize);
	void SetPosition(const int x, const int y);
	void SetFont(const sf::Font& font);
	void SetLimit(const int lim);
	void SetOverflow(const bool state);
	void SetSingleLine(const bool state);
	void SetSelected(const bool state);
	void SetText(const std::string text);

	std::string GetText();

	void Draw(sf::RenderWindow& wind);
	void TypedIn(const sf::Event ev);
	void Click(const sf::Event event, sf::RenderWindow& wind);

private:
	sf::RectangleShape m_background;
	sf::Text m_textbox;
	std::vector<std::string> m_text;
	sf::Font m_font;
	bool m_selected = false;
	bool m_hasLimit = false;
	std::pair<bool, bool> m_overflow = {true, false};
	bool m_singleLine = true;
	int m_limit = 0, m_lineNo = 0, m_dotPos = 0;
	int m_charSize = 30;

	void input(const sf::Event::KeyEvent keyIn, const bool devGoto = false);
	std::string AssembleString();
};

#endif