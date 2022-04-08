#pragma once

#include <string>
#include <fstream>

#include "Encryption.h"

class MasterPassWizard
{
public:
	static std::string get_enc_from_file(std::string filename);
	static bool check(std::string enc_pass, std::string input_pass);
	static void encrypt_and_write(std::string input_pass, std::string filename);
};

