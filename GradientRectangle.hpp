#ifndef GRADIENT_RECTANGLE_HPP
#define GRADIENT_RECTANGLE_HPP

#include <SFML/Graphics.hpp>

class GradientRectangle {
public:
	GradientRectangle(int x, int y, int width, int height);

	void SetColor(sf::Color c1, sf::Color c2, sf::Color c3, sf::Color c4);

	void Draw(sf::RenderWindow& wind);

private:
	sf::Vertex points[4];
};

#endif