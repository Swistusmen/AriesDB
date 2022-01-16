#pragma once

#include "SQLCommand.h"
#include "SQLExceptions.h"

class Where : public SQLCommand
{
public:
    Where() = default;
    Where(Where &&command);

    Where &operator=(Where &&) noexcept;

    ~Where() override;
    int getValidity() override { return validity; };

    std::shared_ptr<Table> execute(std::shared_ptr<Table>) override;

private:
    static const int validity = 3;
};