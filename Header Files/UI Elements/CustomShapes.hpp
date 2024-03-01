#ifndef SPECIAL_SHAPES_HPP
#define SPECIAL_SHAPES_HPP

#include <SFML/Graphics.hpp>

inline sf::ConvexShape RoundedRectangle(
	const float x, const float y, const float width, const float height,
	const float radius, const sf::Color& Col,
	const float Outline = 0.f, const sf::Color& OutlineCol = sf::Color(0, 0, 0),
	const int POINTS = 10
) {
	sf::ConvexShape rrect(static_cast<double>(POINTS) * 4);
	rrect.setOutlineThickness(Outline);
	rrect.setFillColor(Col);
	rrect.setOutlineColor(OutlineCol);
	float X = 0, Y = 0;

	for (int i = 0; i < POINTS; i++) {
		X += radius / POINTS;
		Y = sqrt(radius * radius - X * X);
		rrect.setPoint(i, sf::Vector2f(X + x + width - radius, y - Y + radius));
	}
	Y = 0;
	for (int i = 0; i < POINTS; i++) {
		Y += radius / POINTS;
		X = sqrt(radius * radius - Y * Y);
		rrect.setPoint(i + (double)POINTS, sf::Vector2f(x + width + X - radius, y + height - radius + Y));
	}
	X = 0;
	for (int i = 0; i < POINTS; i++) {
		X += radius / POINTS;
		Y = sqrt(radius * radius - X * X);
		rrect.setPoint(i + (double)POINTS * 2, sf::Vector2f(x + radius - X, y + height - radius + Y));
	}
	Y = 0;
	for (int i = 0; i < POINTS; i++) {
		Y += radius / POINTS;
		X = sqrt(radius * radius - Y * Y);
		rrect.setPoint(i + (double)POINTS * 3, sf::Vector2f(x - X + radius, y + radius - Y));
	}
	return rrect;

}

inline sf::ConvexShape TriangleShape(
	const int x, const int y, const int width, const int height,
	const sf::Color& col, const int outlineWidth = 0,
	const sf::Color& outlineCol = sf::Color::Black
) {
	sf::ConvexShape triangle(3);

	triangle.setPoint(0, sf::Vector2f(x, y));
	triangle.setPoint(1, sf::Vector2f(x + width, y));
	triangle.setPoint(2, sf::Vector2f(x + width / 2, y + height));

	return triangle;
}

#endif