#pragma once
#include "Table.h"
#include <functional>
#include <vector>
#include <string>

class Comparator{
    public:
    Comparator(std::vector<std::function<bool(const std::string&)>>&& compar, std::vector<int>&& ind)
    :comparators(std::move(compar)),indexes(ind){};

    bool operator()(const std::vector<std::string>& row){
            const int noIndexes=indexes.size();
            for(int i=0;i<noIndexes;i++){
                if(!comparators[i](row[indexes[i]]))
                    return false;
            }
            return true;
    }

    private:
        std::vector<std::function<bool(const std::string&)>> comparators;
        std::vector<int> indexes;
};

class make_comparator{
    public:

    Comparator operator()(std::vector<int>&& indexes,const std::vector<std::string>& operators, const std::vector<std::string>& toCompare){
        std::vector<std::function<bool(const std::string&)>>functions;
        const int noOperators=operators.size();
        for(int i=0;i<noOperators;i++){
            if(operators[i]=="<"){
                functions.push_back(greaterThan(toCompare[i]));
            }else if(operators[i]==">"){
                functions.push_back(lessThan(toCompare[i]));
            }else if(operators[i]=="="){
                functions.push_back(equals(toCompare[i]));
            }
        }
        return Comparator(std::move(functions),std::move(indexes));
    }

    private:
    
        struct lessThan{
            lessThan(const std::string& b):val(b){};

            bool operator()(std::string a){
                return a>val;
            }

            std::string val;
        };

        struct greaterThan{
            greaterThan(const std::string& b):val(b){};

            bool operator()(std::string a){
                return a<val;
            }

            std::string val;
        };

        struct equals{
            equals(const std::string& b):val(b){};

            bool operator()(std::string a){
                return a==val;
            }

            std::string val;
        };
};