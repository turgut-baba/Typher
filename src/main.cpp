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
#include "gpu/OpenCL.hpp"

int main(int argc, char* argv)
{
/*     Onnx engine = Onnx();
    //engine.fill();
    engine.Run(); */

    OpenCL gpu = OpenCL();
    gpu.run_kernel();
}

/* end_of_file */
