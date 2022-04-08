#include "CheckBox.h"

CheckBox::CheckBox()
{
}

CheckBox::CheckBox(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f window)
{
	state = false;

	area.setPosition(pos);
	area.setSize(size);
	area.setOutlineThickness(window.y * 0.004f);
	area.setOutlineColor(sf::Color(230, 230, 230));
	area.setFillColor(sf::Color::White);

	this->pos = pos;
	this->size = size;
}

void CheckBox::draw(sf::RenderWindow& window)
{
	window.draw(area);
}

bool CheckBox::onclick(sf::Event event, sf::Vector2i mousePos)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mousePos.y > pos.y && mousePos.y < pos.y + size.y && mousePos.x > pos.x && mousePos.x < pos.x + size.x)
			{
				if (!state) 
				{
					area.setFillColor(sf::Color(230, 230, 230));
				}
				else
				{
					area.setFillColor(sf::Color::White);
				}
				state = !state;
				return true;
			}
		}
	}
	return false;
}

bool CheckBox::get_state()
{
	return state;
}
