#include "Select.h"
#include "Creator.h"

class SelectCreator: public Creator{
    public:
        bool doesAWordRepresentSQLCommand(std::string word) override{
            this->toLower(word);
            return keyWord==word;
        };

        std::unique_ptr<SQLCommand> createASQLCommand()override{
            auto newPtr=std::make_unique<Select>();
            return newPtr;
        }

    private:
    const std::string keyWord="select";
};