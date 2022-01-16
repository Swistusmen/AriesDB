#include<iostream>
#include <string>

struct DBError: public std::exception{
    const char* what() const throw(){
        return "DB error\n";
    }

};

struct NosuchaATable:  public std::exception{
    const char* what() const throw(){
        return "There is no such a table\n";
    }
};

struct WrongArguments:  public std::exception{
    const char* what() const throw(){
        return "Wrong arguments in \n";
    }
};