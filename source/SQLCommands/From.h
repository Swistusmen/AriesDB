#pragma once

#include "ReadCommand.h"

class From : public ReadCommand
{
public:
    From() = default;
    From(From &&command);

    From &operator=(From &&) noexcept;

    ~From() override;

    SQL::Code getPriority() override { return priority; };
    std::unique_ptr<Table> execute(std::unique_ptr<Table>) override;
    std::vector<std::unique_ptr<Table>> execute(const std::vector<DataBaseTable>& tableOfVectors) override;
    void addArgument(const std::string& word) override;

private:
    static const SQL::Code priority= SQL::Code::FROM;
};