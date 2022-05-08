#pragma once

#include <vector>
#include "Grammar.h"
#include "../Logger/Logger.h"
#include <string>
#include <algorithm>

/*
Classes are not virtual cause:
1. They are small
2. They are created in builder method,so in fact using virtual class would cause the could will look nicer,
but would probably slow it
*/
class preCreate{
    public:
        preCreate(const Grammar::Token& _token):
        token(_token){};

        void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
    private:
        const Grammar::Token& token;
};

class preDelete{
    public:
        preDelete(const Grammar::Token& _token):
        token(_token){};

        void operator()(std::vector<Grammar::Token>& tokens,Logger& logger);
    private:
        const Grammar::Token& token;
};

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
