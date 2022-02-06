#include "FileOperations.h"

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

Table loadAFile(std::filesystem::path path,const std::string& filename)
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
        return output;
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

