#ifndef Log_h
#define Log_h

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include "Logger.hpp"
#include "LoggerTerminal.hpp"

enum LogLevel {
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR
};

class Log {
    public:
        static void initialise(LogLevel level, Logger *logger) {
            Log::instance = new Log(level, logger);
        }
    
        static Log& getInstance() {
            if (instance == nullptr) {
                initialise(LOG_INFO, new LoggerTerminal());
            }
            return *instance;
        }
    
        void i(const std::string);
        void d(const std::string);
        void w(const std::string);
        void e(const std::string);
        void operator<<(const std::string);
    
    private:
        static Log *instance;
        Logger *logger;
        LogLevel Level;
    
        Log(LogLevel, Logger *);
        LogLevel level;
        void write(const std::string);
};

#endif /* Log_h */
