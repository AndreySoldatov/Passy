#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include "Button.h"

class Content_panel
{
private:

	sf::RectangleShape line_up;
	sf::RectangleShape line_down;

	sf::String resourse_string;
	sf::Text resourse_text;

	sf::String email_string;
	sf::Text email_text;

	sf::String password_string;
	sf::Text password_text;
	
	sf::RectangleShape back;

	sf::Vector2f pos;
	sf::Vector2f size;

	int index;

public:

	Button delete_btn;

	Content_panel();
	Content_panel(sf::Vector2f pos,
		sf::Vector2f size,
		const sf::String& r,
		const sf::String& e,
		const sf::String& p,
		const sf::Font& font,
		const sf::Font& font_bold,
		sf::Vector2f window,
		int index);

	void draw(sf::RenderWindow &window);
	void scroll_up();
	void scroll_down();
	void get_click(sf::Event event, sf::Vector2i mousePos);

	void set_pass_opacity(int val);

	void set_index(int new_index);

	int get_index();

	std::string get_res();
	std::string get_log();
	std::string get_pass();

	float get_height();
};