#include "On.h"
#include "Creator.h"

class OnCreator: public Creator{
    public:
        bool doesAWordRepresentSQLCommand(std::string word) override{
            this->toLower(word);
            return keyWord==word;
        };

        std::unique_ptr<SQLCommand> createASQLCommand()override{
            auto newPtr=std::make_unique<On>();
            return newPtr;
        }

    private:
    const std::string keyWord="on";
};