#pragma once

#include "ReadCommand.h"
#include <algorithm>

class Select : public ReadCommand
{
public:
    Select() = default;
    Select(Select &&command);

    Select &operator=(Select &&) noexcept;

    ~Select() override;

    SQL::Code getPriority() override { return priority; };
    std::unique_ptr<Table> execute(std::unique_ptr<Table>) override;

private:
    static const SQL::Code priority = SQL::Code::SELECT;
};