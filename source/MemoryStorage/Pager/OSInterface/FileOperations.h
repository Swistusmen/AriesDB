#pragma once
#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <iostream>

#include "../../../Common/Table.h"

#define PATH_SEPARATOR "/"

std::vector<std::string> splitString(std::string val, char delimiter);

std::filesystem::path saveATableIntoATextFile(std::filesystem::path path,const std::string &filename, const Table& table);

Table loadAFile(std::filesystem::path path,const std::string& filename);

std::vector<std::string> listFiles(std::filesystem::path path);

#endif