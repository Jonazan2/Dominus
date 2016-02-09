#ifndef Log_hpp
#define Log_hpp

#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include "Logger.hpp"
#include "LoggerTerminal.hpp"

/// Enum class that represents the different log levels
enum LogLevel {
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR
};

/**
 *  \brief     Log class that uses a logger to log strings. It contains
 *             a minimum log level that determines if a message is going
 *             to be logged.
 *
 *  \author    Jonathan Maldonado
 *  \date      09/02/2016
 */
class Log {
    public:
        static void initialise( LogLevel warningLevel, Logger *logLogger ) {
            logger = logLogger;
            level = warningLevel;
        }
    
        static Log& getInstance() {
            if ( logger == nullptr ) {
                initialise(LOG_INFO, new LoggerTerminal());
            }
            static Log log;
            return log;
        }
    
        void i( const std::string );
        void d( const std::string );
        void w( const std::string );
        void e( const std::string );
        void operator<<( const std::string );
    
    private:
        static Logger *logger;
        static LogLevel level;
    
    	Log() {};
        ~Log();
        void write( const LogLevel, const std::string ) const;
        std::string getLogLevelName( const LogLevel ) const;
};

#endif /* Log_hpp */
