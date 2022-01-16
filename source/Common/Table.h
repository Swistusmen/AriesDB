#pragma once

#include <vector>
#include <string>
#include <list>

struct Table{
        Table(std::string DBName, std::string version):tableName(DBName),tableVersion(version){};
        
        ~Table(){
            columns.clear();
            for(auto row:rows){
                row.clear();
            }
            rows.clear();
        }

        std::string tableName;
        std::string tableVersion;
        std::vector<std::string> columns;
        std::list<std::vector<std::string>> rows;
};
