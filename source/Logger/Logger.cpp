#include "Logger.h"

Logger::Logger(const std::string &saveLocation, const int noSlots)
{
    fileToSaveLocation = saveLocation;
    loadLogs(fileToSaveLocation);
    slots.resize(sizeof(Slot) * noSlots);
    std::fill(slots.begin(), slots.end(), Slot());
}

void Logger::loadLogs(const std::string &location)
{
    auto files = listFiles(getDirectoryPath(location));
    const auto fileName = getFileNameFromPath(location);
    auto logFile = std::find(files.begin(), files.end(), fileName);
    if (logFile == files.end())
    {
        return;
    }
    std::ifstream file;
    file.open(location);
    if (!file.is_open())
    {
        return;
    }
    std::string buffer{""};
    std::vector<std::string> lines;
    while (std::getline(file, buffer))
    {
        if (buffer == LogDelimiter)
        {
            createALogFromVector(lines);
        }
        else
        {
            lines.push_back(buffer);
        }
    }
}

void Logger::createALogFromVector(std::vector<std::string> &lines)
{
    SessionLog newLog(lines[0]);
    newLog.isActive = false;
    newLog.isSaved = true;
    newLog.communicates.push_back(lines[1]);
    logs.push_back(std::move(newLog));
    lines.clear();
}

Logger::~Logger()
{
    saveLogs(fileToSaveLocation);
}

void Logger::saveLogs(const std::string &location)
{
    auto files = listFiles(getDirectoryPath(location));
    const auto fileName = getFileNameFromPath(location);
    auto logFile = std::find(files.begin(), files.end(), fileName);
    if (logFile == files.end())
    {
        std::ofstream file;
        file.open(location);
        file.close();
    }
    std::ofstream file;
    file.open(location, std::ios_base::app);
    if (file.is_open())
    {
        for (auto &it : logs)
        {
            if (it.isActive == false && it.isSaved == false)
            {
                it.isSaved = true;
                saveSingleLog(it, file);
            }
        }

        file.close();
    }
}

void Logger::saveSingleLog(const Logger::SessionLog &log, std::ofstream &file)
{
    /*
    member identifier
    firt command(member input)
    number of rest logs or nothing if there are no other commands
    created date
    last action date
    ------------------\n
    */
    file << log.member << '\n';
    file << log.communicates[0] << '\n';
    if (log.communicates.size() > 1)
    {
        file << log.communicates.size() - 1 << '\n';
        for (int i = 1; i < log.communicates.size(); i++)
        {
            file << log.communicates[i] << '\n';
        }
    }

    file << dateToString(log.created) << '\n';
    file << dateToString(log.lastAction) << '\n';
    file << LogDelimiter << '\n';
}

std::string Logger::dateToString(std::chrono::system_clock::time_point time)
{
    const auto _tTime=std::chrono::system_clock::to_time_t(time);
    const auto*_tTm=localtime(&_tTime);
    const char _dateTimeFormat[]="%Y_%m_%d_%H:%M:%S";
    char _timeStr[]="yyyy_mm_dd_HH-MM.SS.fff";
    strftime(_timeStr,strlen(_timeStr),_dateTimeFormat,_tTm);

    std::string result {_timeStr};
    
    return result;
}

bool Logger::beginSession(const int memberId)
{
    auto freeSlot = std::find_if(slots.begin(), slots.end(), [](const auto &it)
                                 { return it.member == -1; });
    const int index = std::distance(slots.begin(), freeSlot);
    slotsChecker.lock();
    if (!isSlotFree(index))
    {
        slotsChecker.unlock();
        return false;
    }
    createInitLog(index, memberId);
    slotsChecker.unlock();
    return true;
}

void Logger::endSession(const int memberId)
{
    const int slotIndex = getSlotIndex(memberId);
    logs[slots[slotIndex].logIndex].isActive = false;
    slots[slotIndex].member = -1;
}

void Logger::log(const std::string &msg, const int memberId)
{
    auto time = std::chrono::system_clock::now();

    const int index = getLogIndex(memberId);
    logs[index].communicates.emplace_back(msg);
    logs[index].lastAction = time;
}

std::vector<std::string> Logger::getHistory(const int memberId)
{
    std::vector<std::string> history;
    for (const auto &it : logs)
    {
        if (std::stoi(it.member) == memberId)
        {
            history.push_back(it.communicates[0]);
        }
    }
    return history;
}

const Logger::SessionLog &Logger::getLog(const int memberId) const
{
    auto found = std::find_if(logs.cbegin(), logs.cend(), [memberId](const auto &log)
                              { return log.member == std::to_string(memberId) && log.isActive == true; });
    const int index = found - logs.begin();
    return logs[index];
}

bool Logger::wasQuerySuccessful(const int memberId) const
{
    auto log = getLog(memberId);
    return log.communicates.size() == 1;
}

bool Logger::isSlotFree(const int index) const
{
    return slots[index].member == -1;
}

void Logger::createInitLog(const int index, const int memberId)
{
    slots[index].member = memberId;
    logs.emplace_back(std::to_string(memberId));
    const int size = logs.size();
    slots[index].logIndex = size == 0 ? 0 : size - 1;
}

int Logger::getSlotIndex(const int memberId) const
{
    auto found = std::find_if(slots.begin(), slots.end(), [memberId](const auto &it)
                              { return it.member == memberId; });
    return std::distance(slots.begin(), found);
}

int Logger::getLogIndex(const int memberId) const
{
    return slots[getSlotIndex(memberId)].logIndex;
}