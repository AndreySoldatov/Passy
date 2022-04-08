#pragma once

#include <SFML/Graphics.hpp>

class CheckBox
{
private:

	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RectangleShape area;

public:
	bool state;

	CheckBox();
	CheckBox(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f window);

	void draw(sf::RenderWindow& window);
	bool onclick(sf::Event event, sf::Vector2i mousePos);
	bool get_state();
};

