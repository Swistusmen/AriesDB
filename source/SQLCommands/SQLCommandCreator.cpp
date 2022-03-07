#include "SQLCommandCreator.h"

SQLCommandCreator::SQLCommandCreator(){
    creators.push_back(std::make_unique<FromCreator>());
    creators.push_back(std::make_unique<WhereCreator>());
    creators.push_back(std::make_unique<SelectCreator>());
    creators.push_back(std::make_unique<OnCreator>());
}

SQLCommandCreator::~SQLCommandCreator(){
    creators.clear();
}

std::optional<std::unique_ptr<SQLCommand>> SQLCommandCreator::createACommand(std::string word)
{
    //can be higly improved using std::find but first tests
    const int noCreators=creators.size();
    for(int i=0;i<noCreators;i++){
        if(creators[i]->doesAWordRepresentSQLCommand(word)){
            return creators[i]->createASQLCommand();
        }
    }
    return {};
}