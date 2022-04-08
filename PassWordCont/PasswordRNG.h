#pragma once

#include <SFML/Graphics.hpp>

class PasswordRNG
{
private:
	int max_length;
	bool with_symbols;

public:
	PasswordRNG(int max_l);
	sf::String get_rand_password();
	void swap_symbols();
};

