#pragma once

#include <vector>
#include <string>
#include <list>

struct Table{
        Table()=default;
        Table(const std::string& DBName,const std::string& version):tableName(DBName),tableVersion(version){};
        Table(const Table& tab):columns(tab.columns),rows(tab.rows){
            tableName=tab.tableName+"Copy";
            tableVersion="Temporary";
        }
        
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
