#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "../SQLCommands/Commands.h"

namespace Grammar
{
    enum class Lexem
    {
        Command,
        Control_sign,
        Argument,
    };

    struct Token{
        Grammar::Lexem lexem;
        int number;
        std::string expr;
        bool isUsed{false};
    };

    const std::vector<std::string> controlSigns{
        "*"};

    Lexem identifyLexem(const std::string &expr);
    
};