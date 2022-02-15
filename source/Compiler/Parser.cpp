#include "Parser.h"

void Parser::sortCommands(
    std::vector<std::unique_ptr<SQLCommand>> &commands)
{
    std::sort(commands.begin(), commands.end(), [](const auto &a, const auto &b)
              { return a->getPriority() < b->getPriority(); });
}