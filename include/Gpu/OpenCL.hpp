#ifndef GPU_OPENCL_HPP
#define GPU_OPENCL_HPP

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>

#include "Utils/file_ops.hpp"

namespace MLEngine{
    class OpenCL
    {
    public:
        OpenCL();
        ~OpenCL();
        int run_kernel();

        void load_kernel_from_file(std::string file_path);

        std::string get_device_info();
    private:
        char* current_kernel = nullptr;
        size_t global;                      // global domain size for our calculation
        size_t local;                       // local domain size for our calculation

        /**
        * @brief compute device id 
        * 
        */
        cl_device_id device_id;

        /**
         * @brief compute context
         * 
         */
        cl_context context;

        /**
         * @brief compute command queue
         * 
         */
        cl_command_queue commands;          // 
        cl_program program;                 // compute program
        cl_kernel kernel;                   // compute kernel
        
        cl_mem input;                       // device memory used for the input array
        cl_mem output;                      // device memory used for the output array
    };
};

#endif