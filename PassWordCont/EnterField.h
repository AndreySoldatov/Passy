#pragma once

#include <SFML/Graphics.hpp>

class EnterField
{
private:
	sf::RectangleShape area;
	sf::String text;
	sf::String star_filler;
	sf::Text render_text;
	bool active;
	sf::Vector2f pos;
	sf::Vector2f scale;
	int max_size;
	bool fresh;
	bool visible;

public:
	EnterField();
	EnterField(
		const sf::Font& font,
		const sf::String& temp_text,
		sf::Vector2f pos,
		sf::Vector2f scale,
		sf::Vector2f window,
		int max_size = 30);
	sf::String get_text();
	void set_text(sf::String new_text);
	void set_active();
	void set_passive();
	void draw(sf::RenderWindow &window);
	void process_input(sf::Event event);
	bool collided(sf::Vector2i point);
	bool is_fresh();
	void unfresh();
	void swap_string();
	void set_fresh();
};

