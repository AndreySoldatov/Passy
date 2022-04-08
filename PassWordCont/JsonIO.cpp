#include "JsonIO.h"

JsonIO::JsonIO()
{
}

JsonIO::JsonIO(std::string filename)
{
	this->filename = filename;

	this->file_read_handler.open(filename);

	if (!file_read_handler.good()) 
	{
		this->file_read_handler.close();

		this->file_write_handler.open(filename);
		this->file_write_handler << "null";
		this->file_write_handler.close();

		this->file_read_handler.open(filename);
	}

	file_read_handler >> json_object;
	file_read_handler.close();
}

void JsonIO::set_json(std::vector<Content_panel>& content)
{
	json new_json;

	for (auto& panel : content) 
	{
		std::string enc_pass = Encryption::get_encripted_ascii_string(panel.get_log(), panel.get_pass());

		new_json[panel.get_res()]["resource"] = panel.get_res();
		new_json[panel.get_res()]["login"] = panel.get_log();
		new_json[panel.get_res()]["password"] = enc_pass;
	}

	json_object = new_json;
}

std::vector<Content_panel> JsonIO::get_content(const sf::Font &font, const sf::Font& font_bold, sf::Vector2f window)
{
	std::vector<Content_panel> content;

	if (!json_object.is_null()) {
		for (auto& resource : json_object)
		{
			std::string dec_pass = Encryption::get_decripted_ascii_string(
				resource["login"].get<std::string>(),
				resource["password"].get<std::string>());

			content.push_back(Content_panel(sf::Vector2f(0.0f, 160.0f + 30.0f + ((float)content.size() * window.y * 0.1f)),
				sf::Vector2f(window.x, window.y * 0.1f),
				sf::String(resource["resource"].get<std::string>()),
				sf::String(resource["login"].get<std::string>()),
				sf::String(dec_pass),
				font,
				font_bold,
				window,
				content.size() + 1));
		}
	}

	return content;
}

void JsonIO::write_file()
{
	file_write_handler.open(filename);

	file_write_handler << json_object << std::endl;

	file_write_handler.close();
}
