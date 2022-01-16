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

    int getValidity() override { return validity; };
    std::shared_ptr<Table> execute(std::shared_ptr<Table>) override;

private:
    static const int validity = 2;
};