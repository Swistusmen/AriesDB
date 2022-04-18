#include "Grammar.h"

Grammar::Lexem Grammar::identifyLexem(const std::string &expr)
    {
        using namespace Grammar;
        auto res = SQL::toCode(expr);
        if (res != SQL::Code::NONE)
        {
            return Lexem::Command;
        }
        auto sign = std::find(controlSigns.begin(), controlSigns.end(), expr);
        if (sign != controlSigns.end())
        {
            return Lexem::Control_sign;
        }
        return Lexem::Argument;
    }