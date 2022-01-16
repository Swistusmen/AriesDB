#include "Parser.h"

std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> Parser::sortCommands(
    std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> commands)
{
    std::sort(commands->begin(), commands->end(), [](const auto &a, const auto &b)
              { return a->getValidity() < b->getValidity(); });
    return commands;
}