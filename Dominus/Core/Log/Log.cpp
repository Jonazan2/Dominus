#include <Log.hpp>

Log::Log(LogLevel loggingLevel, Logger *logger) {
    this->level = loggingLevel;
    this->logger = logger;
}

void Log::i(const std::string msg) {
    if (level >= LOG_INFO) {
        write(msg);
    }
}

void Log::d(const std::string msg) {
    if (level >= LOG_INFO) {
        write(msg);
    }
}

void Log::w(const std::string msg) {
    if (level >= LOG_INFO) {
        write(msg);
    }
}

void Log::e(const std::string msg) {
    if (level >= LOG_INFO) {
        write(msg);
    }
}

void Log::operator<<(const std::string msg) {
    if (level >= LOG_INFO) {
        write(msg);
    }
}

void Log::write(const std::string msg) {
    std::chrono::time_point<std::chrono::system_clock> currentTime;
    currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
    std::stringstream ss;
    ss <<"[" << std::ctime(&time) << "]: " << msg;
    logger->write(ss.str());
}