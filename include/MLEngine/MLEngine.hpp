#ifndef Typher_HPP
#define Typher_HPP

#include <memory>

namespace TypherEngine{
    enum Runtime{
        None = 0,
        Onnx = 1,
        Tensorflow = 2
    };

    enum KernelEngine{
        None = 0,
        OpenCL = 1,
        Cuda = 2
    };
}

class Typher
{
public:
    static Typher& Instance();

    Typher();

    void set_kernel(TypherEngine::KernelEngine opt);

    void set_runtime(TypherEngine::Runtime opt);
};
#endif