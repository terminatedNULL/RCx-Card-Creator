#ifndef SYSTEM_EVENTS_HPP
#define SYSTEM_EVENTS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <future>



class SystemEventHandler {
public:
	SystemEventHandler(sf::RenderWindow& wind) {
		m_window = &wind;
	}

	void AddEvent(sf::Event& e) {

	}

private:
	sf::RenderWindow* m_window;
};

#endif