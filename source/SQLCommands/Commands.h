#pragma once
#include <string>

namespace SQL{
    enum class Code{
        INSERT,
        CREATE,
        UPDATE,
        DELETE,
        INTO,
        FROM,
        ON, 
        WHERE,
        SELECT,
        JOIN,
        VALUES,
        SET, 
        NONE,
    };

    static Code toCode(std::string code){
        for(auto& it:code){
            it=std::tolower(it);
        }
        if(code=="insert"){
            return Code::INSERT;
        }else if(code =="create"){
            return Code::CREATE;
        }else if(code=="update"){
            return Code::UPDATE;
        }else if(code=="delete"){
            return Code::DELETE;
        }else if(code=="into"){
            return Code::INTO;
        }else if(code=="from"){
            return Code::FROM;
        }else if(code=="on"){
            return Code::ON;
        }else if(code=="where"){
            return Code::WHERE;
        }else if(code=="select"){
            return Code::SELECT;
        }else if(code=="join"){
            return Code::JOIN;
        }else if(code=="values"){
            return Code::VALUES;
        }else if(code=="set"){
            return Code::SET;
        }else{
            return Code::NONE;
        }
    }

    static bool isCompiledTime(const Code& _code){
        if(_code==Code::JOIN){
            return true;
        }else if(_code==Code::INSERT){
            return true;
        }else if(_code==Code::VALUES){
            return true;
        }else if(_code==Code::UPDATE){
            return true; //but not only compile time
        }else if(_code==Code::DELETE){
            return true; //but not only compile time
        }else if(_code==Code::CREATE){
            return true;
        }
        return false;
    }
}
