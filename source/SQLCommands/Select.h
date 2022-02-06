#pragma once

#include "SQLCommand.h"
#include <algorithm>

class Select : public SQLCommand
{
public:
    Select() = default;
    Select(Select &&command);

    Select &operator=(Select &&) noexcept;

    ~Select() override;

    SQL::Code getPriority() override { return priority; };
    std::shared_ptr<Table> execute(std::shared_ptr<Table>) override;

private:
    static const SQL::Code priority = SQL::Code::SELECT;
};