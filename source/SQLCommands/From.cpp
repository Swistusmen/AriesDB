#include "From.h"

From::From(From&& command){
    this->arguments=std::move(command.arguments);
}

From& From::operator= (From&& command)noexcept{
    this->arguments=std::move(command.arguments);
    return *this;
}

From::~From(){

}

std::unique_ptr<Table> From::execute(std::unique_ptr<Table> table){
    if(table->tableName==this->arguments[0])
        return table;
    return nullptr;
}

std::vector<std::unique_ptr<Table>> From::execute(const std::vector<DataBaseTable>& dataTables)
{
    std::vector<std::unique_ptr<Table>> matchingTables;
    
    for(const auto& it: dataTables ){
        auto founded=std::find_if(arguments.begin(),arguments.end(),[&it](auto argument){
            return it.getTableName()==argument;
        });
        if(founded!=arguments.end()){
            matchingTables.emplace_back(std::make_unique<Table>(it.getTableDataForReadOnly()));
        }
    }
    return matchingTables;
}


