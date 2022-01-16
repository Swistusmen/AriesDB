#pragma once
#include <iostream>
#include <string>

std::string takeInputFromKeyboard(std::istream &inputStream)
{
    std::cout << "db > ";
    std::string input;
    inputStream >> input;
    return input;
}
