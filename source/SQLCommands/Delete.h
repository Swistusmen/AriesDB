#pragma once

#include "SQLCommand.h"

class Delete: public SQLCommand{
public:
    Delete() = default;
    Delete(Delete &&command);

    Delete &operator=(Delete &&) noexcept;

    ~Delete() override;

    SQL::Code getPriority() override { return priority; };
    std::unique_ptr<Table> execute(std::unique_ptr<Table>);
    std::vector<std::unique_ptr<Table>> execute(const std::vector<DataBaseTable>& vectorOfTables) override;
    void addArgument(const std::string& word) override;

    const std::string& getTableName(){return tableName;}
    const std::vector<std::string>& getOperators(){return operators;}
    const std::vector<std::string>& getValues(){return values;}
    const std::vector<std::string>& getColumns(){return columns;}

private:
    static const SQL::Code priority= SQL::Code::DELETE;
    std::string tableName {""};
    std::vector<std::string> columns;
    std::vector<std::string> operators;
    std::vector<std::string> values;
};