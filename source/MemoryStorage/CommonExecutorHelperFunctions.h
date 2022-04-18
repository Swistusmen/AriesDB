#pragma once

#include "../Common/Table.h"
#include <memory>

std::unique_ptr<Table> mergeVectorOfResultTablesIntoOne(std::vector<std::unique_ptr<Table>>& tables);
