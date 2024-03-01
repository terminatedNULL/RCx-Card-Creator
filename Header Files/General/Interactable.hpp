#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include <iostream>

#include "SFML/Graphics.hpp"

class Interactable {
public:
	static bool BoundsCheck(const sf::Vector2f pos, const sf::Vector2f size, const sf::RenderWindow& wind);
};

#endif