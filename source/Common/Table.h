#pragma once

#include <vector>
#include <string>
#include <list>

struct Table{
        Table()=default;
        Table(const std::string& DBName,const std::string& version):tableName(DBName),tableVersion(version){};
        Table(const Table& tab):columns(tab.columns),rows(tab.rows){
            tableName=tab.tableName;
            tableVersion="Temporary";
        }
        Table(Table&&)=default;
        Table& operator=(Table&&)=default;
        Table& operator=(const Table& )=default;
        
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
