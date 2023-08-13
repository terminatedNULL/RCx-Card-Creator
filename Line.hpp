#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>

class Line {
public:
    Line(int x1, int y1, int x2, int y2);

    void SetColor(sf::Color c1);

    void SetColor(sf::Color c1, sf::Color c2);

    void Draw(sf::RenderWindow& wind);

private:
    sf::VertexArray line = sf::VertexArray(sf::LineStrip, 2);
    sf::Color pointCols[2] = { sf::Color::Black, sf::Color::Black };
    sf::Vector2f startPos = { 0, 0 };
    sf::Vector2f endPos = { 0, 0 };
};

#endif