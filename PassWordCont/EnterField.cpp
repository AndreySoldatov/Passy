#include "EnterField.h"

EnterField::EnterField() {}

void EnterField::unfresh() 
{
	this->fresh = false;
}

bool EnterField::is_fresh()
{
	return fresh;
}

EnterField::EnterField(
	const sf::Font& font, 
	const sf::String& temp_text, 
	sf::Vector2f pos, 
	sf::Vector2f scale, 
	sf::Vector2f window, 
	int max_size)
{
	this->visible = true;
	this->text = temp_text;
	this->star_filler = "";

	this->pos = pos;
	this->scale = scale;

	this->render_text.setFillColor(sf::Color(100, 100, 100));
	this->render_text.setCharacterSize(scale.y * 0.8f);
	this->render_text.setFont(font);
	this->render_text.setPosition(pos.x + scale.y * 0.1, pos.y);
	this->render_text.setString(text);

	this->area.setFillColor(sf::Color(230, 230, 230));
	this->area.setPosition(pos);
	this->area.setSize(scale);
	this->area.setOutlineColor(sf::Color(230, 230, 230));
	this->area.setOutlineThickness(window.y * 0.004f);

	this->max_size = max_size;

	this->active = false;
	this->fresh = true;
}

sf::String EnterField::get_text()
{
	return this->text;
}

void EnterField::set_text(sf::String new_text)
{
	std::string tmp(new_text.getSize(), '*');
	this->star_filler = tmp;
	this->text = new_text;
	if (visible)
	{
		render_text.setString(text);
	}
	else
	{
		render_text.setString(star_filler);
	}
}

void EnterField::set_active()
{
	if (fresh) 
	{
		text = "";
		render_text.setString(text);
		fresh = false;
	}

	active = true;

	this->render_text.setFillColor(sf::Color(40, 40, 40));

	this->area.setFillColor(sf::Color(255, 255, 255));
}

void EnterField::set_passive()
{
	active = false;

	this->render_text.setFillColor(sf::Color(100, 100, 100));

	this->area.setFillColor(sf::Color(230, 230, 230));
}

void EnterField::process_input(sf::Event event)
{
	if (active)
	{
		if (event.type == sf::Event::TextEntered && event.text.unicode < 128 && event.text.unicode > 31)
		{
			if (text.getSize() < max_size) 
			{
				star_filler += '*';
				text += event.text.unicode;
				if (visible)
				{
					render_text.setString(text);
				}
				else
				{
					render_text.setString(star_filler);
				}
			}
		}

		if (event.type == sf::Event::KeyPressed) 
		{
			if(event.key.code == sf::Keyboard::BackSpace) 
			{
				if (text.getSize() > 0) {
					star_filler.erase(text.getSize() - 1);

					text.erase(text.getSize() - 1);

					if (visible)
					{
						render_text.setString(text);
					}
					else
					{
						render_text.setString(star_filler);
					}
				}
			}
		}
	}
}

bool EnterField::collided(sf::Vector2i point)
{
	if (point.x > pos.x && point.x < pos.x + scale.x && 
		point.y > pos.y && point.y < pos.y + scale.y)
	{
		return true;
	}
	return false;
}

void EnterField::draw(sf::RenderWindow &window)
{
	window.draw(area);
	window.draw(render_text);
}

void EnterField::swap_string() 
{
	this->visible = !this->visible;
	if (visible)
	{
		render_text.setString(text);
	}
	else
	{
		render_text.setString(star_filler);
	}
}

void EnterField::set_fresh()
{
	this->fresh = true;
}