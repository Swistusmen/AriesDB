#pragma once
#include <algorithm>
#include <vector>
#include "ReadCommand.h"
#include "../Common/Algorithms.h"

class On : public ReadCommand
{
public:
    using iter=std::list<std::vector<std::string>>;
    On() = default;
    On(On&&command);

    On &operator=(On &&) noexcept;

    ~On() override;

    SQL::Code getPriority() override { return priority; };

    std::unique_ptr<Table> execute(std::unique_ptr<Table>) override;
    void addArgument(const std::string& word) override;
    std::vector<std::unique_ptr<Table>> execute(std::vector<std::unique_ptr<Table>> & tables) override;
private:
    static const SQL::Code priority= SQL::Code::ON;
};