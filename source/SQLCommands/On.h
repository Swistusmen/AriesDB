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
    std::vector<std::unique_ptr<Table>> execute(std::vector<std::unique_ptr<Table>> & tables) override;

private:
    std::vector<std::unique_ptr<Table>>&& flterTables(std::vector<std::unique_ptr<Table>>& );
    int getIndexOfColumn(const std::vector<std::array<std::string,2>>& tableColumn, std::unique_ptr<Table>& table);
    std::vector<std::pair<iter,std::string>>&& extractColumnValuesAtPointedColumn(std::unique_ptr<Table>&, int index);
    std::vector<std::pair<iter,std::string>>&& leaveOnlyCommonColumnValues(const std::vector<std::pair<iter,std::string>>&,const std::vector<std::pair<iter,std::string>>&);
    std::vector<std::string> getRowToAdd(const std::vector<std::pair<On::iter,std::string>>&map, const std::string& rowValue );

    static const SQL::Code priority= SQL::Code::ON;
};