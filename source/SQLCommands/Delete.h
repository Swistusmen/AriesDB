#pragma once

#include "WriteCommand.h"

class Delete: public WriteCommand{
public:
    Delete() = default;
    Delete(Delete &&command);

    Delete &operator=(Delete &&) noexcept;

    ~Delete() override;

    SQL::Code getPriority() override { return priority; };
    void addArgument(const std::string& word) override;

    bool execute(DataBaseTable& ) override;

private:
    static const SQL::Code priority= SQL::Code::DELETE;
    std::vector<std::string> columns;
    std::vector<std::string> operators;
    std::vector<std::string> values;
};