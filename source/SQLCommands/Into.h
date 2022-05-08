#pragma once

#include "WriteCommand.h"

class Into: public WriteCommand{
public:
    Into() = default;
    Into(Into &&command);

    Into &operator=(Into &&) noexcept;

    ~Into() override;

    SQL::Code getPriority() override { return priority; };
    void addArgument(const std::string& word) override;
    const std::vector<std::string>& getArguments(){return arguments;}
    bool execute(DataBaseTable& ) override;
private:
    static const SQL::Code priority= SQL::Code::INTO;
    std::vector<std::string> arguments;
};