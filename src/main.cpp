/**
 * @file main.cpp
 * @author Turgut Bababalım (turgutbababalim@gmail.com)
 * @brief Entrance of my engine. 
 * @version 0.1
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Inference/Onnx.hpp"
#include "Gpu/OpenCL.hpp"

int main(int argc, char* argv)
{
/*     Onnx engine = Onnx();
    //engine.fill();
    engine.Run(); */
    float data[1024]; 

    for(int i = 0; i < 1024; i++)
        data[i] = rand() / (float)RAND_MAX;

    Typher::OpenCL gpu = Typher::OpenCL();
    gpu.load_kernel_from_file("./kernels/cl/softmax.cl");
    gpu.fill_input<float*>(data, 1024);
    gpu.run_kernel();

    std::cout << "Done." << std::endl;
}

/* end_of_file */

