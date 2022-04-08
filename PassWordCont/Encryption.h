#pragma once

#include <SFML/Graphics.hpp>

class Encryption
{
public:
	static sf::String get_encripted_ascii_string(std::string key_string, std::string msg);
	static sf::String get_encripted_ascii_string(int key, std::string msg);
	static sf::String get_decripted_ascii_string(std::string key_string, std::string msg);
	static sf::String get_decripted_ascii_string(int key, std::string msg);
};