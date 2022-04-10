#include "CommandResult.h"

CommandResult::CommandResult(const CommandResult& _command)
{
    this->executionType=_command.executionType;
    this->result=_command.result;
    *this->output=*_command.output;
}

CommandResult::CommandResult(CommandResult&& _command)
{
    this->executionType=std::move(_command.executionType);
    this->result=std::move(_command.result);
    this->output=std::move(_command.output);
}

CommandResult& CommandResult::operator= (const CommandResult& _command)
{
    this->executionType=_command.executionType;
    this->result=_command.result;
    *this->output=*_command.output;
    return *this;
}

CommandResult& CommandResult::operator=(CommandResult&& _command)
{
    this->executionType=std::move(_command.executionType);
    this->result=std::move(_command.result);
    this->output=std::move(_command.output);
    return *this;
}

CommandResult::~CommandResult()
{
    output.reset();
}

const std::unique_ptr<Table>& CommandResult::getTable() const
{
    return output;
}

const CommandResult::Result& CommandResult::getResult() const
{
    return result;
}

const Commands::ExecutionType& CommandResult::getExecutionType() const
{
    return executionType;
}