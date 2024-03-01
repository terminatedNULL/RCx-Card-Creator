#ifndef GRADIENT_RECTANGLE_HPP
#define GRADIENT_RECTANGLE_HPP

#include <SFML/Graphics.hpp>

class GradientRectangle {
public:
	GradientRectangle(const int x, const int y, const int width, const int height);

	void SetColor(const sf::Color c1, const sf::Color c2, const sf::Color c3, const sf::Color c4);

	void Draw(sf::RenderWindow& wind);

private:
	sf::Vertex m_points[4];
};

#endif