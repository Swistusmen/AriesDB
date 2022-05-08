#include "ReadCommand.h"

ReadCommand::ReadCommand()
{

}

ReadCommand::ReadCommand(ReadCommand &&command)
{
    arguments=std::move(command.arguments);
}

ReadCommand::~ReadCommand()
{
    arguments.clear();
}

std::vector<std::unique_ptr<Table>> ReadCommand::execute(std::vector<std::unique_ptr<Table>> & tables)
{
    std::vector<std::unique_ptr<Table>> vecOfValidTables;
        for (auto &tab : tables)
        {
            auto res = this->execute(std::move(tab));
            if (res != nullptr)
            {
                vecOfValidTables.push_back(std::move(res));
            }
        }
        return vecOfValidTables;
}