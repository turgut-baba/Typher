#include "Utils/file_ops.hpp"

namespace MLUtils
{
    template <typename>
    struct always_false : std::false_type {};

    template<typename ArgType>
    [[nodiscard]] std::string read_file(ArgType filepath)
    {
        std::ifstream file(filepath, std::ios::binary);
        
        if (!file) 
        {
            throw std::ios_base::failure("Error: Unable to open file.");
        }

        std::ostringstream content_stream;
        content_stream << file.rdbuf();
        
        return content_stream.str();
    }

    template std::string read_file<std::string&>(std::string&);
    template std::string read_file<std::string>(std::string);
    template std::string read_file<char const*>(char const*);
}