#include "Algorithms.h"

std::array<std::string, 2> getTableNameAndColumnNameFromArgument(const std::string &argument)
{
    size_t npos = argument.find_last_of('.');
    std::array<std::string, 2> result;
    result[0] = argument.substr(0, npos);
    result[1] = argument.substr(npos + 1, argument.size() - 1);
    return result;
}

std::vector<std::string> splitString(const std::string& arg,char splitter){
    std::vector<std::string> result;
    result.push_back("");
    for(const auto& it: arg){
        if(it!=splitter){
            result.back()+=it;
        }else{
            result.push_back("");
        }
    }
    if(result.back()==""){
        result.pop_back();
    }
    return result;
}
