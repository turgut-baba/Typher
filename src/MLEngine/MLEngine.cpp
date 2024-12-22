#include "Typher.hpp"

Typher& Typher::Instance()
{
    static std::unique_ptr<Typher> instance = std::make_unique<Typher>(); 

    return *instance;
};

Typher::Typher()
{

}

void Typher::set_kernel(TypherEngine::KernelEngine opt)
{

}

void Typher::set_runtime(TypherEngine::Runtime opt)
{

}

