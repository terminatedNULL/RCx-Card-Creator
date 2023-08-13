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
	Textbox(float x, float y, int width, int height, std::string text);

	void BackgroundBorderDetails(sf::Color bgCol, sf::Color borderCol, int borderWidth);
	void SetColor(sf::Color col);
	void SetCharacterSize(int cSize);
	void SetPosition(int x, int y);
	void SetFont(sf::Font& font);
	void SetLimit(int lim);
	void SetOverflow(bool state);
	void SetSingleLine(bool state);
	void SetSelected(bool state);
	void SetText(std::string text);

	std::string GetText();

	void Draw(sf::RenderWindow& wind);
	void TypedIn(sf::Event ev);
	void Click(sf::Event event, sf::RenderWindow& wind);

private:
	sf::RectangleShape m_background;
	sf::Text m_textbox;
	std::vector<std::string> m_text;
	sf::Font m_font;
	bool m_selected = false;
	bool m_hasLimit = false;
	std::pair<bool, bool> m_overflow = {true, false};
	bool m_singleLine = true;
	int m_limit = 0, lineNo = 0, dotPos = 0;
	int m_charSize = 30;

	void input(sf::Event::KeyEvent keyIn, bool devGoto = false);
	std::string AssembleString();
};

#endif