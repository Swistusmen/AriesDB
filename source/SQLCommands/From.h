#pragma once

#include "SQLCommand.h"
#include <exception>

//From for now only with 1 argument

class From : public SQLCommand
{
public:
    From() = default;
    From(From &&command);

    From &operator=(From &&) noexcept;

    ~From() override;

    SQL::Code getPriority() override { return priority; };
    std::shared_ptr<Table> execute(std::shared_ptr<Table>) override;
    std::vector<std::shared_ptr<Table>> execute(const std::vector<DataBaseTable>& tableOfVectors) override;

private:
    static const SQL::Code priority= SQL::Code::FROM;
};