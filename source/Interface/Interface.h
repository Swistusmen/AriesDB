#pragma once
#include <iostream>
#include <string>

std::string takeInputFromKeyboard()
{
    std::cout << "db > ";
    std::string input;
    std::getline(std::cin,input);
    return input;
}
