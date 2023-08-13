#ifndef WINDOW_BASE_HPP
#define WINDOW_BASE_HPP

#include "SFML/Graphics.hpp"

class WindowBase {
public:
	virtual void HandleEvents(sf::Event& event, sf::RenderWindow& wind) = 0;
	virtual void Draw(sf::RenderWindow& wind) = 0;
	virtual void Open(sf::RenderWindow& wind) = 0;
	virtual void Close() = 0;
	virtual bool IsActive() = 0;
};

#endif