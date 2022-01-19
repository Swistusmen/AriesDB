#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <iostream>

#include "../../../Common/Table.h"

std::filesystem::path saveATableIntoATextFile(std::filesystem::path path,const std::string &filename, std::shared_ptr<Table> table)
{
    if (table == nullptr)
    {
        throw new std::invalid_argument("Passed table is a nullptr");
    }
    std::ofstream file;
    std::string newFile = path.string() + "/" + filename;

    file.open(newFile);
    if (file.is_open())
    {
        std::for_each(table->columns.begin(), table->columns.end(), [&file](auto a)
                      { file << a << " "; });
        file << '\n';
        std::for_each(table->rows.begin(), table->rows.end(), [&file](auto row)
                      {
                          std::for_each(row.begin(), row.end(), [&file](auto value)
                                        { file << value + ' '; });
                          file << '\n';
                      });
        file.close();
    }
    return path;
}
/*
std::filesystem::path appendAFile(std::filesystem::path path,std::string filename, std::shared_ptr<Table> table, int noLine);

std::shared_ptr<Table> loadAFile(std::filesystem::path path,std::string filename);
*/
std::vector<std::string> listFiles(std::filesystem::path path)
{
    std::vector<std::string> files;
    for (const auto &it : std::filesystem::directory_iterator(path))
    {
        files.push_back(std::filesystem::absolute(it.path()).string());
    }
    return files;
}
