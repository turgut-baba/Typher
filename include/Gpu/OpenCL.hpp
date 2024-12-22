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

namespace Typher{

    
    class OpenCL
    {
    public:

        /**
        * @brief compute device id 
        * 
        */
        OpenCL();

        /**
        * @brief compute device id 
        * 
        */
        ~OpenCL();

        /**
        * @brief compute device id 
        * 
        */
        int run_kernel();

        /**
        * @brief compute device id 
        * 
        */
        void load_kernel_from_file(std::string file_path);

        /**
        * @brief compute device id 
        * 
        */
        std::string get_device_info();

        template<typename data_type>
        void fill_input(data_type data, size_t size)
        {
            this->data = data;
        }
    private:
        float* data;
        /**
        * @brief compute device id 
        * 
        */
        char* current_kernel = nullptr;

        /**
        * @brief compute device id 
        * 
        */
        size_t global;                      // global domain size for our calculation

        /**
        * @brief compute device id 
        * 
        */
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
        cl_command_queue commands;

        /**
        * @brief compute device id 
        * 
        */
        cl_program program;                 // compute program

        /**
        * @brief compute device id 
        * 
        */
        cl_kernel kernel;                   // compute kernel
        
        /**
        * @brief compute device id 
        * 
        */
        cl_mem input;                       // device memory used for the input array

        /**
        * @brief compute device id 
        * 
        */
        cl_mem output;                      // device memory used for the output array
    };
};

#endif