#include "Encryption.h"

sf::String Encryption::get_encripted_ascii_string(std::string key_string, std::string msg)
{
    sf::String enc_string = "";
    int offset = 0;

    for (auto c : key_string)
    {
        offset += c;
    }

    for (size_t i = 0; i < msg.length(); i++)
    {
        enc_string += (unsigned int)((offset + (int)(msg[i])) % 94 + 33);
    }

    return enc_string;
}

sf::String Encryption::get_encripted_ascii_string(int key, std::string msg)
{
    sf::String enc_string = "";

    for (size_t i = 0; i < msg.length(); i++)
    {
        enc_string += (unsigned int)((key + (int)(msg[i])) % 94 + 33);
    }

    return enc_string;
}

sf::String Encryption::get_decripted_ascii_string(std::string key_string, std::string msg)
{
    sf::String dec_string = "";
    int offset = 0;

    for (auto c : key_string)
    {
        offset += c;
    }

    for (size_t i = 0; i < msg.length(); i++)
    {
        int tmp = -(offset + 33) + (int)(msg[i]);
        tmp = ((tmp % 94 + 94) % 94);
        dec_string += (unsigned int)(tmp > 33 ? tmp : tmp + 94);
    }

    return dec_string;
}

sf::String Encryption::get_decripted_ascii_string(int key, std::string msg)
{
    sf::String dec_string = "";

    for (size_t i = 0; i < msg.length(); i++)
    {
        int tmp = -(key + 33) + (int)(msg[i]);
        tmp = ((tmp % 94 + 94) % 94);
        dec_string += (unsigned int)(tmp > 33 ? tmp : tmp + 94);
    }

    return dec_string;
}
