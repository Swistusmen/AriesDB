#include<iostream>
#include <string>

struct DBError: public std::exception{
    const char* what() const throw(){
        return "DB error";
    }

};

struct NosuchaATable:  public std::exception{
    const char* what() const throw(){
        return "There is no such a table";
    }
};