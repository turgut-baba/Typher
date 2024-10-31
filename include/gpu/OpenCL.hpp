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

class OpenCL
{
public:
    OpenCL();

    int run_kernel();
};

#endif