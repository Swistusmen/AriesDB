#pragma once

#include "SQLCommand.h"

class Into: public SQLCommand{
public:
    Into() = default;
    Into(Into &&command);

    Into &operator=(Into &&) noexcept;

    ~Into() override;

    SQL::Code getPriority() override { return priority; };
    std::unique_ptr<Table> execute(std::unique_ptr<Table>);
    std::vector<std::unique_ptr<Table>> execute(const std::vector<DataBaseTable>& vectorOfTables) override;
    void addArgument(const std::string& word) override;
    const std::string& getTableName();

private:
    static const SQL::Code priority= SQL::Code::INTO;
    std::string tableName {""};
};