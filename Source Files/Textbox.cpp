#include "Textbox.hpp"

using namespace TextTools;

Textbox::Textbox(float x, float y, int width, int height, std::string text) {
	m_background.setSize(sf::Vector2f(width, height));
	m_background.setPosition(sf::Vector2f(x, y));
	m_background.setFillColor(sf::Color(255, 255, 255));
	m_textbox.setPosition(sf::Vector2f(x + 2, y));
	m_text.push_back(text);
	m_textbox.setString(text);
	m_textbox.setFillColor(sf::Color(0, 0, 0));
}

//=============================================================================================
// SET FUNCTIONS
//=============================================================================================

void Textbox::BackgroundBorderDetails(sf::Color bgCol, sf::Color borderCol, int borderWidth) {
	m_background.setFillColor(bgCol);
	m_background.setOutlineColor(borderCol);
	m_background.setOutlineThickness(borderWidth);
}

void Textbox::SetColor(sf::Color col) {
	m_textbox.setFillColor(col);
}

void Textbox::SetCharacterSize(int cSize) {
	m_textbox.setCharacterSize(cSize);
	m_charSize = cSize;
}

void Textbox::SetPosition(int x, int y) {
	m_background.setPosition(sf::Vector2f(x, y));
	m_textbox.setPosition(sf::Vector2f(x, y));
}

void Textbox::SetFont(const sf::Font& font) {
	m_textbox.setFont(font);
	m_font = font;
}

void Textbox::SetLimit(int lim) {
	m_hasLimit = true;
	m_limit = lim;
}

void Textbox::SetOverflow(bool state) {
	m_overflow.first = state;
}

void Textbox::SetSingleLine(bool state) {
	m_singleLine = state;
}

void Textbox::SetSelected(bool state) {
	if (m_selected != state) {
		m_selected = state;
		if (!state) {
			m_textbox.setString(AssembleString());
		}
		else {
			m_textbox.setString(AssembleString() + "_");
		}
	}
}

/*
 * This is definitely a hack, which uses a hidden default argument to input() to jump to the PASTE
 * section of the code which just so happens to do the exact checking that we want for this function.
 * By passing in a blank event and manually setting the clipboard to whatever we want to be processed
 * (restoring the clipboard's contents following) it works!
 */
void Textbox::SetText(std::string text) {
	sf::Event::KeyEvent e = { sf::Keyboard::Key::A, false, false, false };
	std::string contents = sf::Clipboard::getString();
	sf::Clipboard::setString(text);
	input(e, true);
	sf::Clipboard::setString(contents);
}

//=============================================================================================
// GET FUNCTIONS
//=============================================================================================

std::string Textbox::GetText() {
	return AssembleString();
}

//=============================================================================================
// BASE FUNCTIONS
//=============================================================================================

void Textbox::Draw(sf::RenderWindow& wind) {
	wind.draw(m_background);
	wind.draw(m_textbox);
}

void Textbox::TypedIn(sf::Event ev) {
	if (m_selected) {
		input(ev.key);
	}
}

void Textbox::Click(sf::Event event, sf::RenderWindow& wind) {
	if (BoundsCheck(m_background.getPosition(), m_background.getSize(), wind)) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			SetSelected(true);
		}
	}
	else {
		SetSelected(false);
	}
}

//=============================================================================================
// INTERNAL FUNCTIONS
//=============================================================================================

void Textbox::input(sf::Event::KeyEvent keyIn, bool devGoto) {
	if (devGoto) { goto SAFE_TEXT_SET; }
	if (keyIn.code != DELETE_K && keyIn.code != ENTER && keyIn.code != ESCAPE && keyIn.code != PASTE) {
		const sf::Vector2f addCharBounds = textSize(std::to_string(keyIn.code), m_font, m_charSize);
		const sf::Vector2f lineTextBounds = textSize(m_text[m_lineNo], m_font, m_charSize);

		if (m_singleLine) {
			if (lineTextBounds.x + addCharBounds.x - 10 > m_background.getSize().x + 2) {
				if (!m_overflow.first && m_dotPos == 0) {
					m_overflow.second = true;
					m_dotPos = m_text[0].length() - 1;
				}
			}
			m_text[0] += static_cast<char>(keyIn.code);
		}
		else {
			if (lineTextBounds.x + addCharBounds.x - 10 > m_background.getSize().x + 2) {
				if (!m_overflow.first) { m_overflow.second = true; }
				m_lineNo++;
				m_text.emplace_back("");
				m_text[m_lineNo] += static_cast<char>(keyIn.code);
			}
			else {
				m_text[m_lineNo] += static_cast<char>(keyIn.code);
			}
		}
	}
	else if (keyIn.code == DELETE_K && m_text[m_lineNo].length() > 0) {
		if (m_singleLine) {
			if ((m_text[0].length() - 1) == m_dotPos) {
				m_overflow.second = false;
				m_dotPos = 0;
			}
			m_text[0].pop_back();
		}
		else {
			if (m_text[m_lineNo].length() == 0) {
				m_overflow.second = false;
				m_lineNo--;
				m_text.pop_back();
			}
			else {
				m_text[m_lineNo].pop_back();
			}
		}
	}
	else if (keyIn.code == ENTER && !m_singleLine) {
		m_lineNo++;
		m_text.emplace_back("");
	}
	else if (keyIn.code == ESCAPE) {
		SetSelected(false);
		return;
	}
	else if (keyIn.code == PASTE && m_singleLine) { //Implement multi-line pasting at some point
	SAFE_TEXT_SET:
		m_text.clear();
		m_text.emplace_back("");
		m_lineNo = 0;
		const std::string clipContents = sf::Clipboard::getString();

		if (textSize(clipContents, m_font, m_charSize).x > m_background.getSize().x) {
			for (int i = 0; i < clipContents.length(); i++) {
				const sf::Vector2f lineTextBounds = textSize(m_text[0], m_font, m_charSize);
				const sf::Vector2f addCharBounds = textSize(std::to_string(clipContents[i]), m_font, m_charSize);
				if (lineTextBounds.x + addCharBounds.x - 10 > m_background.getSize().x + 2) {
					if (!m_overflow.first && m_dotPos == 0) {
						m_overflow.second = true;
						m_dotPos = m_text[0].length() - 1;
					}
				}
				m_text[0] += clipContents[i];
			}
		}
		else {
			m_text[0] = clipContents;
			m_textbox.setString(clipContents);
			return;
		}
	}

	if (m_overflow.second) {
		if (m_singleLine) {
			m_textbox.setString(m_text[0].substr(0, m_dotPos - 1) + "...");
		}
		else m_textbox.setString(m_text[0].substr(0, m_text[0].length() - 2) + "...");
		return;
	}
	m_textbox.setString(AssembleString() + "_");
}

std::string Textbox::AssembleString() {
	std::string assembledString;

	for (auto& s : m_text) { assembledString.append(s + '\n'); }
	assembledString.pop_back();

	return assembledString;
}