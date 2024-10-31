#include "Utils/string_ops.hpp"

bool checkModelExtension(const std::string& filename)
{
    if(filename.empty())
    {
        throw std::runtime_error("[ ERROR ] The Model file path is empty");
    }

    size_t pos = filename.rfind('.');

    if (pos == std::string::npos)
        return false;

    std::string ext = filename.substr(pos+1);

    if (ext == "onnx")
        return true;

    return false;
}
