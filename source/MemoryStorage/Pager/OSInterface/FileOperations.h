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

#define PATH_SEPARATOR "/"

std::vector<std::string> splitString(std::string val, char delimiter){
    std::vector<std::string> output;
    std::string buffer;
    for(auto it=val.begin();it!=val.end();it++){
        if(*it==delimiter){
            output.push_back(buffer);
            buffer="";
        }else{
            buffer+=*it;
        }
    }
    return output;
}
/*
std::filesystem::path saveATableIntoATextFile(std::filesystem::path path,const std::string &filename, std::shared_ptr<Table> table)
{
    if (table == nullptr)
    {
        throw new std::invalid_argument("Passed table is a nullptr");
    }
    std::ofstream file;
    std::string newFile = path.string() + PATH_SEPARATOR + filename;

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
    }else{
        throw new std::invalid_argument("Could not open a file");
    }
    return path;
}*/

std::filesystem::path saveATableIntoATextFile(std::filesystem::path path,const std::string &filename, const Table& table)
{
    std::ofstream file;
    std::string newFile = path.string() + PATH_SEPARATOR + filename;

    file.open(newFile);
    if (file.is_open())
    {
        std::for_each(table.columns.begin(), table.columns.end(), [&file](auto a)
                      { file << a << " "; });
        file << '\n';
        std::for_each(table.rows.begin(), table.rows.end(), [&file](auto row)
                      {
                          std::for_each(row.begin(), row.end(), [&file](auto value)
                                        { file << value + ' '; });
                          file << '\n';
                      });
        file.close();
    }else{
        throw new std::invalid_argument("Could not open a file");
    }
    return path;
}

//std::filesystem::path appendAFile(std::filesystem::path path,std::string filename, std::shared_ptr<Table> table, int noLine);not needed now
/*
std::shared_ptr<Table> loadAFile(std::filesystem::path path,const std::string& filename)
{
    std::ifstream file;
    std::string fileToRead=path.string()+PATH_SEPARATOR+filename;
    file.open(fileToRead);
    std::shared_ptr<Table> output;
    if(file.is_open()){
        output=std::make_shared<Table>("DTO","1");
        std::string buffer;
        std::getline(file,buffer);
        output->columns=std::move(splitString(buffer,' '));
        buffer="";
        while(std::getline(file,buffer)){
                output->rows.push_back(std::move(splitString(buffer,' ')));
                buffer="";
        }
        file.close();
    }else{
        throw new std::invalid_argument("Could not open a file to load");
    }
    return output;
}*/

Table&& loadAFile(std::filesystem::path path,const std::string& filename)
{
    std::ifstream file;
    std::string fileToRead=path.string()+PATH_SEPARATOR+filename;
    file.open(fileToRead);
    if(file.is_open()){
        Table output("DTO","1");
        std::string buffer;
        std::getline(file,buffer);
        output.columns=std::move(splitString(buffer,' '));
        buffer="";
        while(std::getline(file,buffer)){
                output.rows.push_back(std::move(splitString(buffer,' ')));
                buffer="";
        }
        file.close();
        return std::move(output);
    }else{
        throw new std::invalid_argument("Could not open a file to load");
    }
}

std::vector<std::string> listFiles(std::filesystem::path path)
{
    std::vector<std::string> files;
    for (const auto &it : std::filesystem::directory_iterator(path))
    {
        files.push_back(std::filesystem::absolute(it.path()).string());
    }
    return files;
}
