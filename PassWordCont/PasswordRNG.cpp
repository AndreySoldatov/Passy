#include "PasswordRNG.h"

PasswordRNG::PasswordRNG(int max_l)
{
	srand(time(nullptr));
	this->max_length = max_l;
	with_symbols = false;
}

sf::String PasswordRNG::get_rand_password()
{
	std::string pass = "";

	char randomASCII[4];
	
	for (size_t i = 0; i < max_length; i++)
	{
		randomASCII[0] = rand() % 10 + 48;
		randomASCII[1] = rand() % 26 + 65;
		randomASCII[2] = rand() % 26 + 97;
		randomASCII[3] = rand() % 15 + 33;
		pass.push_back(randomASCII[rand()%(with_symbols ? 4 : 3)]);
	}
	return sf::String(pass);
}

void PasswordRNG::swap_symbols()
{
	with_symbols = !with_symbols;
}
