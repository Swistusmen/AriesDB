#pragma once

#include <vector>
#include "Grammar.h"
#include "../Logger/Logger.h"
#include <string>
#include <algorithm>

class preUpdate{
    public:
        preUpdate(const Grammar::Token& _token):
        token(_token){};

        void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
    private:
        const Grammar::Token& token;
};

class preValues{
public:
    preValues(const Grammar::Token& _token):
        token(_token){};

    void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
private:
    const Grammar::Token& token;
};

class preJoin{
public:
    preJoin(const Grammar::Token& _token):token(_token){};

    void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
private:
    const Grammar::Token& token;
};

class preStar{
public:
    preStar(const Grammar::Token& _token):token(_token){};

    void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
private:
    const Grammar::Token& token;
};

class preInsert{
public:
    preInsert(const Grammar::Token& _token):token(_token){};

    void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
private:
    const Grammar::Token& token;
};
