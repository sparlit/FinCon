#include "CrashHandler.h"
#include "Logger.h"
#include <csignal>
#include <iostream>

namespace FinConCore {

void FinConSignalHandler(int signal) {
    FINCON_LOG_ERROR("CRASH", "Caught signal: " + std::to_string(signal));
    exit(signal);
}

void FinConCrashHandler::install() {
    std::signal(SIGSEGV, FinConSignalHandler);
    std::signal(SIGFPE, FinConSignalHandler);
    std::signal(SIGILL, FinConSignalHandler);
    std::signal(SIGABRT, FinConSignalHandler);
}

}
