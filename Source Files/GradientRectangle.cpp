#include "GradientRectangle.hpp"

GradientRectangle::GradientRectangle(int x, int y, int width, int height) {
	points[0] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Black);
	points[1] = sf::Vertex(sf::Vector2f(x + width, y), sf::Color::Black);
	points[2] = sf::Vertex(sf::Vector2f(x + width, y + height), sf::Color::Black);
	points[3] = sf::Vertex(sf::Vector2f(x, y + height), sf::Color::Black);
}

void GradientRectangle::SetColor(sf::Color c1, sf::Color c2, sf::Color c3, sf::Color c4) {
	points[0].color = c1;
	points[1].color = c2;
	points[2].color = c3;
	points[3].color = c4;
}

void GradientRectangle::Draw(sf::RenderWindow& wind) {
	wind.draw(points, 4, sf::Quads);
}