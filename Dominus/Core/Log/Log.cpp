#include <Log.hpp>

Logger *Log::logger = nullptr;
LogLevel Log::level = LOG_INFO;

void Log::i( const std::string msg ) {
    if ( LOG_INFO >= Log::level ) {
        write(LOG_INFO, msg);
    }
}

void Log::d( const std::string msg ) {
    if ( LOG_DEBUG >= Log::level ) {
        write(LOG_DEBUG, msg);
    }
}

void Log::w( const std::string msg ) {
    if ( LOG_WARNING >= Log::level ) {
        write(LOG_WARNING, msg);
    }
}

void Log::e( const std::string msg ) {
    if ( LOG_ERROR >= Log::level ) {
        write(LOG_ERROR, msg);
    }
}

void Log::operator<<( const std::string msg ) {
    if ( LOG_DEBUG >= Log::level ) {
        write(LOG_DEBUG, msg);
    }
}

std::string Log::getLogLevelName( const LogLevel level ) const {
    switch ( level ) {
        case LOG_INFO:
            return "INFO";
        case LOG_DEBUG:
            return "DEBUG";
        case LOG_ERROR:
            return "ERROR";
        case LOG_WARNING:
            return "WARNING";
        default:
            break;
    }
}

void Log::write( const LogLevel level, const std::string msg ) const {
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    std::stringstream ss;
    ss <<"<" << getLogLevelName(level) << ">" <<
    "[" << currentTime->tm_hour
    << ":" << currentTime->tm_min << ":"
    << currentTime->tm_sec <<"]: " << msg;
    Log::logger->write(ss.str());
}

Log::~Log() {
    delete logger;
};