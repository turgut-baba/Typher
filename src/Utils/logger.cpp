#include "logger.hpp"

namespace MLUtils
{
    Logger::Logger(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logger_mutex_);

        for(LogLevel& level: active_levels)
        {
                
        }

        this->set_level(level);

        if (backtrace_n_messages_ > 0) {
            new_logger->enable_backtrace(backtrace_n_messages_);
        }
    }

    void Logger::set_level(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logger_mutex_);

        this->level = level;
    }


    std::string Logger::level_to_string(LogLevel level) const
    {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }



};
