#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>

class Line {
public:
    Line(const int x1, const int y1, const int x2, const int y2);

    void SetColor(const sf::Color c1);

    void SetColor(const sf::Color c1, const sf::Color c2);

    void Draw(sf::RenderWindow& wind);

private:
    sf::VertexArray m_line = sf::VertexArray(sf::LineStrip, 2);
    sf::Color m_pointCols[2] = { sf::Color::Black, sf::Color::Black };
    sf::Vector2f m_startPos = { 0, 0 };
    sf::Vector2f m_endPos = { 0, 0 };
};

#endif