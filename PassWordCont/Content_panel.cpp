#include "Content_panel.h"

Content_panel::Content_panel()
{
}

Content_panel::Content_panel(sf::Vector2f pos, 
	sf::Vector2f size, 
	const sf::String &r, 
	const sf::String &e, 
	const sf::String &p, 
	const sf::Font &font,
	const sf::Font &font_bold,
	sf::Vector2f window,
	int index)
{
	this->pos = pos;
	this->size = size;
	this->index = index;

	this->resourse_string = r;
	this->email_string = e;
	this->password_string = p;

	this->back.setFillColor(sf::Color::White);
	this->back.setPosition(pos);
	this->back.setSize(sf::Vector2f(size.x, size.y));

	this->line_up.setFillColor(sf::Color(230, 230, 230));
	this->line_up.setPosition(pos);
	this->line_up.setSize(sf::Vector2f(size.x, size.y * 0.05f));

	this->line_down.setFillColor(sf::Color(230, 230, 230));
	this->line_down.setPosition(pos + sf::Vector2f(0, size.y));
	this->line_down.setSize(sf::Vector2f(size.x, size.y * 0.05f));

	this->resourse_text.setFillColor(sf::Color(rand() % 120 + 40, rand() % 120 + 40, rand() % 120 + 40));
	this->resourse_text.setCharacterSize(size.y * 0.35f);
	this->resourse_text.setFont(font_bold);
	this->resourse_text.setPosition(pos.x + size.y * 0.6, pos.y + size.y * 0.3f);
	this->resourse_text.setString(std::to_string(index) + ". " + resourse_string);

	this->email_text.setFillColor(sf::Color(40, 40, 40));
	this->email_text.setCharacterSize(size.y * 0.35f);
	this->email_text.setFont(font);
	this->email_text.setPosition(size.x * 0.25f, pos.y + size.y * 0.3f);
	this->email_text.setString(email_string);

	this->password_text.setFillColor(sf::Color(40, 40, 40));
	this->password_text.setCharacterSize(size.y * 0.35f);
	this->password_text.setFont(font);
	this->password_text.setPosition(size.x * 0.55f, pos.y + size.y * 0.3f);
	this->password_text.setString(password_string);

	this->delete_btn = Button(
		sf::Vector2f(size.x * 0.9f, pos.y + size.y * 0.3f), 
		sf::Vector2f(size.x * 0.1f, size.y * 0.4f),
		"delete",
		font,
		window);
}

void Content_panel::draw(sf::RenderWindow& window)
{
	window.draw(back);
	window.draw(line_up);
	window.draw(line_down);
	
	window.draw(resourse_text);
	window.draw(email_text);
	window.draw(password_text);
	delete_btn.draw(window);
}

void Content_panel::scroll_up()
{
	back.move(0, -size.y);
	resourse_text.move(0, -size.y);
	email_text.move(0, -size.y);
	password_text.move(0, -size.y);

	line_down.move(0, -size.y);
	line_up.move(0, -size.y);

	delete_btn.move(sf::Vector2f(0, -size.y));

	pos.y -= size.y;
}

void Content_panel::scroll_down()
{
	back.move(0, size.y);
	resourse_text.move(0, size.y);
	email_text.move(0, size.y);
	password_text.move(0, size.y);

	line_down.move(0, size.y);
	line_up.move(0, size.y);

	delete_btn.move(sf::Vector2f(0, size.y));

	pos.y += size.y;
}

void Content_panel::get_click(sf::Event event, sf::Vector2i mousePos)
{
	const std::string text = password_string;
	const size_t len = text.length() + 1;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (mousePos.y > pos.y && mousePos.y < pos.y + size.y && mousePos.x < size.x * 0.9) 
			{
				back.setFillColor(sf::Color(230, 230, 230));

				HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
				memcpy(GlobalLock(hMem), text.c_str(), len);
				GlobalUnlock(hMem);
				OpenClipboard(0);
				EmptyClipboard();
				SetClipboardData(CF_TEXT, hMem);
				CloseClipboard();
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			back.setFillColor(sf::Color::White);
		}
	}
}

void Content_panel::set_pass_opacity(int val)
{
	sf::Color old_color = this->password_text.getFillColor();
	this->password_text.setFillColor(sf::Color(old_color.r, old_color.g, old_color.b, val));
}

void Content_panel::set_index(int new_index)
{
	this->index = new_index;
	this->resourse_text.setString(std::to_string(index) + ". " + resourse_string);
}

int Content_panel::get_index()
{
	return this->index;
}

std::string Content_panel::get_res()
{
	return resourse_string;
}

std::string Content_panel::get_log()
{
	return email_string;
}

std::string Content_panel::get_pass()
{
	return password_string;
}

float Content_panel::get_height()
{
	return pos.y;
}
