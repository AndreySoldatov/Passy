#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:

	sf::Vector2f pos;
	sf::Vector2f size;
	sf::String label_string;
	sf::Text label_text;
	sf::RectangleShape area;

public:

	Button();
	Button(sf::Vector2f pos, sf::Vector2f size, const sf::String &str, const sf::Font &font, sf::Vector2f window);

	void draw(sf::RenderWindow& window);
	bool onclick(sf::Event event/*, void(*action)()*/, sf::Vector2i mousePos);
	void move(sf::Vector2f delta);
};

