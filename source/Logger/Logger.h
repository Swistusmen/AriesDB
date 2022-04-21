#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <fstream>
#include <iostream>
#include "../MemoryStorage/Pager/OSInterface/FileOperations.h"
#include <cstring>

class Logger{
public:
    Logger(const std::string& saveLocation, const int noSlots);
    ~Logger();

    bool beginSession(const int memberId);
    void endSession(const int memberId);

    void log(const std::string& msg, const int memberId);

    std::vector<std::string> getHistory(const int memberId);

    struct SessionLog{
        std::string member;
        std::vector<std::string> communicates;
        const std::chrono::system_clock::time_point created;
        std::chrono::system_clock::time_point lastAction;
        bool isActive{false};
        bool isSaved{false};

        SessionLog(const std::string& mem):member(mem),isActive(true),
            created(std::chrono::system_clock::now()),lastAction(created){}
    };

    const SessionLog& getLog(const int memberId) const;
    bool wasQuerySuccessful(const int memberId) const;

private:
    void saveLogs(const std::string& filename);
    void loadLogs(const std::string& filename);

    void saveSingleLog(const Logger::SessionLog& log, std::ofstream& file);
    std::string dateToString(std::chrono::system_clock::time_point time);
    void createInitLog(const int index, const int memberId);
    bool isSlotFree(const int index) const;
    int getSlotIndex(const int memberId) const;
    int getLogIndex(const int memberId) const;
    void createALogFromVector(std::vector<std::string>& lines);
    
private:

    struct Slot{
        int member {-1};
        int logIndex{-1};
    };

    std::vector<Slot> slots;  
    std::vector<SessionLog> logs;
    std::string fileToSaveLocation;
    std::mutex slotsChecker;
    const std::string LogDelimiter{"------------------------------"};
};