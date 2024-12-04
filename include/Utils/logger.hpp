#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>

// TODO: to achieve this you must make everything into an instance.
#define LOG(logger, message) logger.log(message, __FILE__, __LINE__)

namespace MLUtils
{
    enum class LogLevel
    { 
        DEBUG, 
        INFO, 
        WARNING, 
        ERROR, 
        CRITICAL 
    };

    class Logger
    {
    public:
        Logger(Logger& copy) = delete;
        Logger(Logger&& move) = delete;

        Logger& operator=(Logger& copy) = delete;
        Logger& operator=(Logger&& move) = delete;

        explicit Logger(LogLevel level);

        ~Logger();

        std::string level_to_string(LogLevel level) const noexcept;

        void set_level(LogLevel level);

        template<typename T, typename ... Args>
        void log(const T&& item, const Args&&... args);

    private:
        std::ofstream logFile; 
        LogLevel level;
        std::mutex logger_mutex_;
    };
};

#endif