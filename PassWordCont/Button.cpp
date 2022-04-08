#include "Button.h"

Button::Button()
{
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, const sf::String& str, const sf::Font& font, sf::Vector2f window)
{
	this->pos = pos;
	this->size = size;

	this->label_string = str;

	this->label_text.setFillColor(sf::Color(40, 40, 40));
	this->label_text.setCharacterSize(window.y * 0.025f);
	this->label_text.setFont(font);
	this->label_text.setPosition(
		pos.x + (size.x - label_string.getSize() * (window.y * 0.015f)) / 2.0f, 
		pos.y + (size.y - window.y * 0.030f) / 2.0f);
	this->label_text.setString(label_string);

	this->area.setFillColor(sf::Color::White);
	this->area.setOutlineColor(sf::Color(230, 230, 230));
	this->area.setOutlineThickness(window.y * 0.004f);
	this->area.setPosition(pos);
	this->area.setSize(size);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(area);
	window.draw(label_text);
}

bool Button::onclick(sf::Event event/*, void(*action)()*/, sf::Vector2i mousePos)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mousePos.y > pos.y && mousePos.y < pos.y + size.y && mousePos.x > pos.x && mousePos.x < pos.x + size.x)
			{
				area.setFillColor(sf::Color(230, 230, 230));
				return true;
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			area.setFillColor(sf::Color::White);
		}
	}
	return false;
}

void Button::move(sf::Vector2f delta)
{
	pos += delta;
	area.move(delta);
	label_text.move(delta);
}
