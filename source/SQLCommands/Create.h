#pragma once

#include "SQLCommand.h"

class Create: public SQLCommand{
public:
    Create() = default;
    Create(Create &&command);

    Create &operator=(Create &&) noexcept;

    ~Create() override;

    SQL::Code getPriority() override { return priority; };
    std::unique_ptr<Table> execute(std::unique_ptr<Table>);
    std::vector<std::unique_ptr<Table>> execute(const std::vector<DataBaseTable>& vectorOfTables) override;
    void addArgument(const std::string& word) override;
    const std::string& getTableName(){return tableName;};

private:
    static const SQL::Code priority= SQL::Code::CREATE;
    std::string tableName {""};
};