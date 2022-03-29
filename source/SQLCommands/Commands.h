#pragma once
#include <string>

namespace SQL{
    enum class Code{
        FROM,
        ON, 
        WHERE,
        SELECT,
        JOIN,
        NONE,
    };

    static Code toCode(std::string code){
        for(auto& it:code){
            it=std::tolower(it);
        }
        if(code=="from"){
            return Code::FROM;
        }else if(code=="on"){
            return Code::ON;
        }else if(code=="where"){
            return Code::WHERE;
        }else if(code=="select"){
            return Code::SELECT;
        }else if(code=="join"){
            return Code::JOIN;
        }else{
            return Code::NONE;
        }
    }

    static bool isCompiledTime(const Code& _code){
        if(_code==Code::JOIN){
            return true;
        }
        return false;
    }
}
