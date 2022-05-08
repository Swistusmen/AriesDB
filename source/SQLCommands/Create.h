#pragma once

#include "ReorganizeCommand.h"

class Create: public ReorganizeCommand{
public:
    Create() = default;
    Create(Create &&command);

    Create &operator=(Create &&) noexcept;

    ~Create() override;

    SQL::Code getPriority() override { return priority; };

    void addArgument(const std::string& word) override;

private:
    static const SQL::Code priority= SQL::Code::CREATE;
};