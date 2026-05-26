#include "CrashHandler.h"
#include "Logger.h"
#include <csignal>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace core {

void signalHandler(int signal) {
    LOG_ERROR("CRASH", "Caught signal: " + std::to_string(signal));
    // In a real app, generate stack trace/minidump here
    exit(signal);
}

void CrashHandler::install() {
    std::signal(SIGSEGV, signalHandler);
    std::signal(SIGFPE, signalHandler);
    std::signal(SIGILL, signalHandler);
    std::signal(SIGABRT, signalHandler);
}

}
