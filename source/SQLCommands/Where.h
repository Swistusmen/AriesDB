#pragma once

#include "SQLCommand.h"

class Where : public SQLCommand
{
public:
    Where() = default;
    Where(Where &&command);

    Where &operator=(Where &&) noexcept;

    ~Where() override;
    SQL::Code getPriority() override { return priority; };

    std::unique_ptr<Table> execute(std::unique_ptr<Table>) override;

private:
    static const SQL::Code priority = SQL::Code::WHERE;
};