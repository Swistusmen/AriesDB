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
#include <optional>
#include <iostream>

#include "../../../Common/Table.h"
#include "../../../Common/Algorithms.h"

#define PATH_SEPARATOR "/"

std::optional<std::filesystem::path> saveATableIntoATextFile(std::filesystem::path path,const std::string &filename, const Table& table);

std::optional<Table> loadAFile(std::filesystem::path path,const std::string& filename);

std::vector<std::string> listFiles(std::filesystem::path path);

std::string getDirectoryPath(const std::string& filepath);

std::string getFileNameFromPath(const std::string& filepath);

void deleteFile(std::filesystem::path path,const std::string &filename);

#endif