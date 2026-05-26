#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <iostream>
#include <QDateTime>

namespace core {

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    static Logger& instance() {
        static Logger inst;
        return inst;
    }

    void log(LogLevel level, const std::string& tag, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
        std::string levelStr;
        switch (level) {
            case LogLevel::Debug: levelStr = "DEBUG"; break;
            case LogLevel::Info: levelStr = "INFO"; break;
            case LogLevel::Warning: levelStr = "WARN"; break;
            case LogLevel::Error: levelStr = "ERROR"; break;
        }

        std::string formatted = timestamp.toStdString() + " [" + levelStr + "] [" + tag + "] " + message;

        std::cerr << formatted << std::endl;
        if (logFile_.is_open()) {
            logFile_ << formatted << std::endl;
        }
    }

private:
    Logger() {
        logFile_.open("terminal.log", std::ios::app);
    }
    ~Logger() {
        if (logFile_.is_open()) logFile_.close();
    }

    std::mutex mutex_;
    std::ofstream logFile_;
};

#define LOG_DEBUG(tag, msg) core::Logger::instance().log(core::LogLevel::Debug, tag, msg)
#define LOG_INFO(tag, msg) core::Logger::instance().log(core::LogLevel::Info, tag, msg)
#define LOG_WARN(tag, msg) core::Logger::instance().log(core::LogLevel::Warning, tag, msg)
#define LOG_ERROR(tag, msg) core::Logger::instance().log(core::LogLevel::Error, tag, msg)

} // namespace core
