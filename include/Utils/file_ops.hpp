#ifndef FILE_OPS_HPP
#define FILE_OPS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include <sstream>

namespace MLUtils
{
    template<typename ArgType  = std::string&>
    [[nodiscard]] std::string read_file(ArgType filepath);
}

#endif 