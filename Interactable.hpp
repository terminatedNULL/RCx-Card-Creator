#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include <iostream>

#include "SFML/Graphics.hpp"

class Interactable {
public:
	bool BoundsCheck(sf::Vector2f pos, sf::Vector2f size, sf::RenderWindow& wind);
};

#endif