#include "Interface/Interface.h"
#include "Compiler/Tokenizer.h"
#include "Compiler/Parser.h"
#include "Common/Table.h"
#include "MemoryStorage/DataWarehouse.h"
#include <iostream>

int main()
{
    /*std::cout << "Hello world\n";
    std::cout << takeInputFromKeyboard(std::cin) << std::endl;*/

    Tokenizer tokenizer;
    std::string test="where category Fashion";
    auto tokens=tokenizer.tokenizeInputString(test);

    Parser parser;
    tokens=parser.sortCommands(std::move(tokens));
    
    DataWarehouse db;
    auto ptrToTable=tokens->at(0)->execute(db.tab);
    std::cout<<(ptrToTable==nullptr)<<std::endl;
    std::for_each(ptrToTable->rows.begin(),ptrToTable->rows.end(),[](auto row){
        std::for_each(row.begin(),row.end(),[](auto element){
            std::cout<<element<<" ";
        });
        std::cout<<std::endl;
    })    ;


    return 0;
}