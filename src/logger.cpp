#include "logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>

std::mutex logMutex;

std::string current_time() {
    auto now = std::chrono::system_clock::now();
    auto in_time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time), "%H:%M:%S")
       << "." << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

void log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::string levelStr;
    std::string color;

    switch (level) {
        case INFO:
            levelStr = "INFO";
            color = "\033[1;32m"; // green
            break;
        case DEBUG:
            levelStr = "DEBUG";
            color = "\033[1;34m"; // blue
            break;
        case ERROR:
            levelStr = "ERROR";
            color = "\033[1;31m"; // red
            break;
    }

    std::cout << color
              << "[" << levelStr << "] [" << current_time() << "] "
              << message << "\033[0m" << std::endl;
}

