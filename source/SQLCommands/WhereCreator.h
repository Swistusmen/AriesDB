#include "Where.h"
#include "Creator.h"

class WhereCreator: public Creator{
    public:
        bool doesAWordRepresentSQLCommand(std::string word) override{
            this->toLower(word);
            std::cout<<word<<std::endl;
            return keyWord==word;
        };

        std::unique_ptr<SQLCommand> createASQLCommand()override{
            auto newPtr=std::make_unique<Where>();
            return newPtr;
        }

    private:
    const std::string keyWord="where";
};