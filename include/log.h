#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include "../tool/tool.h"

extern class LOG log;

class Tool;

enum LogLevel {
    TRACK,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class LOG {
public:
    // 禁止拷贝构造和拷贝赋值
    LOG(const LOG&) = delete;
    LOG& operator=(const LOG&) = delete;
    //日志的目标文件设置
    LOG(const std::string& logFile = "") : logFileName(logFile) {
        if (!logFileName.empty()) {
            fileStream.open(logFileName, std::ios::app);
            if (!fileStream.is_open()) {
                std::cerr << "Log initialization failed!!!!" << std::endl;
                exit(-1);
            }
        }
    }

    ~LOG() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
    }

    template <typename T>
    LOG& operator<<(const T& message) {

        std::lock_guard<std::mutex> lock(logMutex);

        if (fileStream.is_open()) {
            fileStream <<  message << std::endl;
        }
        return *this;
    }
    LOG& operator<<(LogLevel level) {
        std::string timestamp = Tool::getTimestamp();
        std::string logLevelStr = getLogLevelString(level);
        std::string logHead = timestamp + " - " + logLevelStr + " - ";
        std::lock_guard<std::mutex> lock(logMutex);
        if (fileStream.is_open()) {
            fileStream << logHead;
        }
        
        return *this;
    }

private:

    std::string logFileName;
    std::ofstream fileStream;
    std::mutex logMutex;
    std::string getLogLevelString(LogLevel level) {
        switch (level) {
            case TRACK: return "TRACK";
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            case CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }
public:

};

#define LOG_TRACK         log << TRACK
#define LOG_DEBUG         log << DEBUG
#define LOG_INFO          log << INFO 
#define LOG_WARNING       log << WARNING
#define LOG_ERROR         log << ERROR
#define LOG_CRITICAL      log << CRITICAL