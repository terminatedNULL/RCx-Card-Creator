#include "Interactable.hpp"

bool Interactable::BoundsCheck(sf::Vector2f pos, sf::Vector2f size, sf::RenderWindow& wind) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(wind);
	sf::Vector2f realPos = wind.mapPixelToCoords(mousePos);
	if (realPos.x > pos.x && realPos.x < pos.x + size.x) {
		if (realPos.y > pos.y && realPos.y < pos.y + size.y) {
			return true;
		}
	}
	return false;
}