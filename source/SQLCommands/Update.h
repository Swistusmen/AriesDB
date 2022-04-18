#pragma once

#include "SQLCommand.h"

class Update: public SQLCommand{
public:
    Update() = default;
    Update(Update &&command);

    Update &operator=(Update &&) noexcept;

    ~Update() override;

    SQL::Code getPriority() override { return priority; };
    std::unique_ptr<Table> execute(std::unique_ptr<Table>);
    std::vector<std::unique_ptr<Table>> execute(const std::vector<DataBaseTable>& vectorOfTables) override;
    void addArgument(const std::string& word) override;
    const std::string& getTableName();

    const std::vector<std::string>& getConditionalValues(){return conditionValues;}
    const std::vector<std::string>& getConditionalOperators(){return conditionOperators;}
    const std::vector<std::string>& getConditionalColumns(){return conditionColumns;}
    const std::vector<std::string>& getValues(){return values;}
    const std::vector<std::string>& getValuesColumns(){return valuesColumns;}

private:
    static const SQL::Code priority= SQL::Code::UPDATE;
    std::string tableName {""};
    std::vector<std::string>conditionValues;
    std::vector<std::string>conditionColumns;
    std::vector<std::string>conditionOperators;
    std::vector<std::string>valuesColumns;
    std::vector<std::string>values;
    int noValuesAfterWhichAddToConditionNotArgumentsNorTableName{-1};

    void addToConditional(const std::string&);
    void addToValues(const std::string&);
};