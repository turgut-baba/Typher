#include "../include/Typher/Typher.hpp"

int main()
{
    Typher typher = Typher();

    typher.set_kernel(TypherEngine::OpenCL);
    typher.set_runtime(TypherEngine::Onnx);
    //From now on gpu
    auto softmax = typher.set_kernel();

    auto ret = softmax.execute();

    
}