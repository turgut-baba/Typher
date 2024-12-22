#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <vector>
#include <exception>
#include <memory>

// TODO: to achieve this you must make everything into an instance.
#define LOG(...) Logger::instance().log(__FILE__, __LINE__, __VA__ARGS__)

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

        static void initialize_logger(LogLevel level);

        static Logger& instance();

        ~Logger();

        std::string level_to_string(LogLevel level) const noexcept;

        void set_level(LogLevel level);

        void set_flush(bool flush);

        void enable_file_dump(bool enable);
        
private:
        inline std::ostream& line_end(std::ostream& os);

public:
        template<typename ... Args>
        void log(std::string file, std::string line, const Args&&... args)
        {
            std::cout << "[LOG] {Line: " << line << ", File: " << file << "}: ";
            ((std::cout << args << " "), ...);
            std::cout << line_end;
        }

        void flush();

        template<typename T, typename ... Args>
        void debug(const T&& item, const Args&&... args);
    private:
        explicit Logger(LogLevel level);
        
        std::ofstream logFile; 
        LogLevel level;
        std::vector<LogLevel> active_levels;

        bool DEBUG = false;
        bool INFO = false;
        bool WARNING = false;
        bool CRITICAL = false;
        bool ERROR = true;
        
        bool should_flush = false;
    };
};

#endif