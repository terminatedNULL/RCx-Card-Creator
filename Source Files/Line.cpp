#include "Line.hpp"

Line::Line(int x1, int y1, int x2, int y2) {
    m_line[0].position = sf::Vector2f(x1, y1);
    m_line[1].position = sf::Vector2f(x2, y2);
}

void Line::SetColor(sf::Color c1) {
    m_line[0].color = c1;
    m_line[1].color = c1;
}

void Line::SetColor(sf::Color c1, sf::Color c2) {
    m_line[0].color = c1;
    m_line[1].color = c2;
}

void Line::Draw(sf::RenderWindow& wind) {
    wind.draw(m_line);
}