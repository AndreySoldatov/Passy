#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <algorithm>

#include "Content_panel.h"
#include "Encryption.h"

using json = nlohmann::json;

class JsonIO
{
private:
	std::ifstream file_read_handler;
	std::ofstream file_write_handler;
	std::string filename;

public:
	json json_object;

	JsonIO();

	JsonIO(std::string filename);
	
	void set_json(std::vector<Content_panel> &content);
	std::vector<Content_panel> get_content(const sf::Font& font, const sf::Font& font_bold, sf::Vector2f window);

	void write_file();
};

