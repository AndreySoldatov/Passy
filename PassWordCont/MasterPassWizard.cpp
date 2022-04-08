#include "MasterPassWizard.h"

std::string MasterPassWizard::get_enc_from_file(std::string filename)
{
    std::ifstream input_handler(filename);
    std::string str;
    if (input_handler.is_open())
    {
        std::getline(input_handler, str);
        input_handler.close();
    }

    return Encryption::get_decripted_ascii_string(996209, str);
}

bool MasterPassWizard::check(std::string enc_pass, std::string input_pass)
{
    return false;
}

void MasterPassWizard::encrypt_and_write(std::string input_pass, std::string filename)
{
    std::ofstream file_writer(filename);

    file_writer << Encryption::get_encripted_ascii_string(996209, input_pass).toAnsiString();

    file_writer.close();
}
