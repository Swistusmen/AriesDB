#pragma once
#include <algorithm>
#include <vector>
#include "SQLCommand.h"


//TODO: create subset of commonly used functions

std::array<std::string,2> getTableNameAndColumnNameFromArgument(const std::string& argument);

class On : public SQLCommand
{
public:
    using iter=std::list<std::vector<std::string>>;
    On() = default;
    On(On&&command);

    On &operator=(On &&) noexcept;

    ~On() override;

    SQL::Code getPriority() override { return priority; };

    std::unique_ptr<Table> execute(std::unique_ptr<Table>) override;
    void addArgument(const std::string& word) override;
    std::vector<std::unique_ptr<Table>> execute(std::vector<std::unique_ptr<Table>> & tables) override;
private:
    int getIndexOfColumn(const std::vector<std::array<std::string,2>>& tableColumn, std::unique_ptr<Table>& table);
    
    static const SQL::Code priority= SQL::Code::ON;
};