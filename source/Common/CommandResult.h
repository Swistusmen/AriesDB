#pragma once

#include <string>
#include "Table.h"
#include <memory>
#include "../SQLCommands/ExecutionType.h"

class CommandResult{
    public:
        enum class Result{
            Success,
            Failure,
        };

        const std::unique_ptr<Table>& getTable() const;
        const Result& getResult() const;
        const Commands::ExecutionType& getExecutionType() const;

        CommandResult(const Result _result, const Commands::ExecutionType _exec, std::unique_ptr<Table>&& table):
            executionType(_exec),result(_result),output(std::move(table)){};

        CommandResult(const Result _result, const Commands::ExecutionType _exec):
            executionType(_exec),result(_result){};

        CommandResult(const CommandResult&);
        CommandResult(CommandResult&&);
        CommandResult& operator=(const CommandResult&);
        CommandResult& operator=(CommandResult&&);
        ~CommandResult();

    private:
        std::unique_ptr<Table> output {nullptr};
        Result result;
        Commands::ExecutionType executionType;
};