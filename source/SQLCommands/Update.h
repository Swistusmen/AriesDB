#pragma once

#include "WriteCommand.h"

class Update: public WriteCommand{
public:
    Update() = default;
    Update(Update &&command);

    Update &operator=(Update &&) noexcept;

    ~Update() override;

    SQL::Code getPriority() override { return priority; };
    void addArgument(const std::string& word) override;

    bool execute(DataBaseTable&)override;

private:
    static const SQL::Code priority= SQL::Code::UPDATE;
    std::vector<std::string>conditionValues;
    std::vector<std::string>conditionColumns;
    std::vector<std::string>conditionOperators;
    std::vector<std::string>valuesColumns;
    std::vector<std::string>values;
    int noValuesAfterWhichAddToConditionNotArgumentsNorTableName{-1};

    void addToConditional(const std::string&);
    void addToValues(const std::string&);
};