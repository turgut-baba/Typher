#include "Utils/Logger/logger.hpp"

namespace MLUtils
{
    Logger* _logger_instance = nullptr;
    std::mutex logger_mutex_;

    void Logger::initialize_logger(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logger_mutex_);

        _logger_instance = new Logger(level);

        std::atexit([]() { // Register destructor with atexit
            delete _logger_instance;
            _logger_instance = nullptr;
        });
    }

    Logger& Logger::instance()
    {
        std::lock_guard<std::mutex> lock(logger_mutex_);

        return *_logger_instance;
    }

    Logger::Logger(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logger_mutex_);

        set_level(level);

        this->set_level(level);

/*         if (backtrace_n_messages_ > 0) 
        {
            new_logger->enable_backtrace(backtrace_n_messages_);
        } */
    }

    void Logger::flush()
    {
        std::cout.flush();
    }

    inline std::ostream& Logger::line_end(std::ostream& os) {
        if (should_flush) {
            os.flush(); // Explicitly flush if the condition is true
        }
        return os;
    }

    // Overload operator<< for flush_or_not
    std::ostream& operator<<(std::ostream& os, std::ostream& (*func)(std::ostream&)) {
        return func(os);
    }

    void Logger::set_flush(bool flush)
    {
        this->should_flush = flush;
    }

    void Logger::set_level(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logger_mutex_);

        this->level = level;

        switch (level) {
            case LogLevel::CRITICAL:
                DEBUG = true;
            case LogLevel::ERROR:
                ERROR = true;
            case LogLevel::WARNING:
                WARNING = true;
            case LogLevel::INFO:
                INFO = true;
            case LogLevel::DEBUG:
                DEBUG = true;
            default:
                throw std::runtime_error("Wrong log level.");
        }
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
