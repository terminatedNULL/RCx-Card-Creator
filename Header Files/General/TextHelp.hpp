#ifndef TEXT_HELP_HPP
#define TEXT_HELP_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace TextTools {
	inline sf::Vector2f textSize(std::string text, sf::Font& font, int size) {
		sf::Text sizeText(text, font);
		sizeText.setCharacterSize(size);
		return { sizeText.getGlobalBounds().width, sizeText.getGlobalBounds().height };
	}

	/*
	 * This whole function is stupid, and was only created because SFML cannot figure out how to correctly bound text.
	 */
	inline sf::Vector2f centerText(int x, int y, sf::Text text, sf::Font& font, int sizeX = 0, int sizeY = 0) {
		const std::string criteria("abcdefghijklmnopqrstuvwxyz0123456789()_-., ");
		const std::string textStr = text.getString();

		if (textStr.find('p') != std::string::npos) {
			const sf::Text pText(std::string("p"), font, text.getCharacterSize());
			const int pSize = pText.getGlobalBounds().height / 2;

			return {
				x - text.getGlobalBounds().width / 2 + sizeX / 2,
				y - text.getGlobalBounds().height + sizeY / 2 + pSize
			};
		}
		else {
			/*
			 * This is a clever little hack to stop SFML from screwing the text centering up, as for some
			 * reason it does not know how to make actual bounding boxes for the text (or the font - not sure).
			 * The centering is only particularly bad when a string containing only lower-case letters is positioned,
			 * so we just make a new version of the string with an 'A' on either side, fixing the bounding box.
			 *
			 * I'm sure there's to be a way to correctly adjust the bounding boxes for the text, sometime I'll
			 * make a header designed to do just that, but I really don't want to, so this will have do for the moment.
			 */
			if (textStr.find_first_not_of(criteria) == std::string::npos) {
				const sf::Text sizeText("A" + textStr + "A", font, text.getCharacterSize());
				return {
					x - text.getGlobalBounds().width / 2 + sizeX / 2,
					y - sizeText.getGlobalBounds().height + sizeY / 2 + 2
				};
			}

			return {
				x - text.getGlobalBounds().width / 2 + sizeX / 2,
				y - text.getGlobalBounds().height + sizeY / 2 + 2
			};
		}
	}
}

#endif