#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

enum LogLevel {
    INFO,
    DEBUG,
    ERROR
};

void log(LogLevel level, const std::string& message);

#endif // LOGGER_HPP


