#include "FileOperations.h"

std::optional<std::filesystem::path> saveATableIntoATextFile(std::filesystem::path path,const std::string &filename, const Table& table)
{
    std::ofstream file;
    std::string newFile = path.string() + PATH_SEPARATOR + filename;

    file.open(newFile);
    if (file.is_open())
    {
        std::for_each(table.columns.begin(), table.columns.end(), [&file](auto a)
                      { file << a << WORDS_SEPARATOR; });
        file << '\n';
        std::for_each(table.rows.begin(), table.rows.end(), [&file](auto row)
                      {
                          std::for_each(row.begin(), row.end(), [&file](auto value)
                                        { file << value + WORDS_SEPARATOR; });
                          file << '\n';
                      });
        file.close();
        return path;
    }
    return {};
}

void deleteFile(std::filesystem::path path,const std::string &filename)
{
    std::cout<<path.string() + PATH_SEPARATOR + filename<<std::endl;
    std::filesystem::remove(path.string() + PATH_SEPARATOR + filename);
}

std::optional<Table> loadAFile(std::filesystem::path path,const std::string& filename)
{
    std::ifstream file;
    std::string fileToRead=path.string()+PATH_SEPARATOR+filename;
    size_t npos=filename.find_last_of(".");
    std::string rawFilenName=filename.substr(0,npos);
    file.open(fileToRead);
    if(file.is_open()){
        Table output(rawFilenName,"1");
        std::string buffer;
        std::getline(file,buffer);
        output.columns=std::move(splitString(buffer,WORDS_SEPARATOR));
        buffer="";
        while(std::getline(file,buffer)){
                output.rows.push_back(std::move(splitString(buffer,WORDS_SEPARATOR)));
                buffer="";
        }
        file.close();
        return output;
    }else{
        return {};
    }
}

std::vector<std::string> listFiles(std::filesystem::path path)
{
    std::vector<std::string> files;
    for (const auto &it : std::filesystem::directory_iterator(path))
    {
        files.push_back(std::filesystem::absolute(it.path()).filename().string());
    }
    return files;
}

std::string getDirectoryPath(const std::string& filepath)
{
    return std::filesystem::path(filepath).parent_path();
}

std::string getFileNameFromPath(const std::string& filepath)
{
    return std::filesystem::path(filepath).filename();
}