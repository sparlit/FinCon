#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <iostream>
#include <QDateTime>

namespace FinConCore {

enum class FinConLogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class FinConLogger {
public:
    static FinConLogger& instance() {
        static FinConLogger inst;
        return inst;
    }

    void log(FinConLogLevel level, const std::string& tag, const std::string& message) {
        std::lock_guard<std::mutex> lock(FinConLogger_Mutex);
        QString FinConStr_Timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
        std::string levelStr;
        switch (level) {
            case FinConLogLevel::Debug: levelStr = "DEBUG"; break;
            case FinConLogLevel::Info: levelStr = "INFO"; break;
            case FinConLogLevel::Warning: levelStr = "WARN"; break;
            case FinConLogLevel::Error: levelStr = "ERROR"; break;
        }

        std::string formatted = FinConStr_Timestamp.toStdString() + " [" + levelStr + "] [" + tag + "] " + message;

        std::cerr << formatted << std::endl;
        if (FinConLogger_File.is_open()) {
            FinConLogger_File << formatted << std::endl;
        }
    }

private:
    FinConLogger() {
        FinConLogger_File.open("terminal.log", std::ios::app);
    }
    ~FinConLogger() {
        if (FinConLogger_File.is_open()) FinConLogger_File.close();
    }

    std::mutex FinConLogger_Mutex;
    std::ofstream FinConLogger_File;
};

#define FINCON_LOG_DEBUG(tag, msg) FinConCore::FinConLogger::instance().log(FinConCore::FinConLogLevel::Debug, tag, msg)
#define FINCON_LOG_INFO(tag, msg) FinConCore::FinConLogger::instance().log(FinConCore::FinConLogLevel::Info, tag, msg)
#define FINCON_LOG_WARN(tag, msg) FinConCore::FinConLogger::instance().log(FinConCore::FinConLogLevel::Warning, tag, msg)
#define FINCON_LOG_ERROR(tag, msg) FinConCore::FinConLogger::instance().log(FinConCore::FinConLogLevel::Error, tag, msg)

}
