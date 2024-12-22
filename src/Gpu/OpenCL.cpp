#include "Gpu/OpenCL.hpp"

#define DATA_SIZE (1024)

namespace Typher{

    OpenCL::OpenCL()
    {
        cl_int CL_err = CL_SUCCESS;
        cl_uint numPlatforms = 0;

        std::cout << "Getting platforms... \n" << std::endl;

        CL_err = clGetPlatformIDs( 0, NULL, &numPlatforms );

        if (CL_err == CL_SUCCESS)
            std::cout << numPlatforms << " platform(s) found\n" << std::endl;
        else
            std::cout << "clGetPlatformIDs(" << CL_err <<  ")\n" << std::endl;

        // BELOW WAS ORIGINALLY IN RUN_KERNEL.

        // Connect to a compute device
        //
        int err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, 1, &device_id, NULL);

        if (err != CL_SUCCESS)
        {
            printf("Error: Failed to create a device group! %d\n", err);
        }
    
        // Create a compute context 
        //
        context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
        if (!context)
        {
            printf("Error: Failed to create a compute context!\n");
        }

        // Create a command commands
        //
        commands = clCreateCommandQueue(context, device_id, 0, &err);
        if (!commands)
        {
            printf("Error: Failed to create a command commands!\n");
        }
    }

    std::string OpenCL::get_device_info()
    {
        char *driver_version = nullptr;
        clGetDeviceInfo(0, CL_DRIVER_VERSION, sizeof(char*), &driver_version, NULL);

        return {driver_version};
    }

    void OpenCL::load_kernel_from_file(std::string file_path)
    {
        if(this->current_kernel != nullptr)
        {
            delete[] this->current_kernel;
        }
        
        size_t dotPosition = file_path.find_last_of('.');

        if(dotPosition == std::string::npos || file_path.substr(dotPosition) != ".cl")
        {
            // TODO: log error
        }else{
            std::string str_file = MLUtils::read_file(file_path);

            const char* as_c_str = str_file.c_str();

            this->current_kernel = new char[strlen(as_c_str) + 1];

            std::strcpy(this->current_kernel, as_c_str);
        }
    }

    int OpenCL::run_kernel()
    {
        int err;                            // error code returned from api calls
        
        float results[DATA_SIZE];           // results returned from device

        unsigned int correct;               // number of correct results returned
        
        // Fill our data set with random float values
        //
        unsigned int count = DATA_SIZE;

        // Create the compute program from the source buffer
        //
        program = clCreateProgramWithSource(context, 1, (const char **) & this->current_kernel, NULL, &err);
        if (!program)
        {
            printf("Error: Failed to create compute program!\n");
            return EXIT_FAILURE;
        }

        // Build the program executable
        //
        err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
        if (err != CL_SUCCESS)
        {
            size_t len;
            char buffer[2048];

            printf("Error: Failed to build program executable!\n");
            clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
            printf("%s\n", buffer);
            exit(1);
        }

        // Create the compute kernel in the program we wish to run
        //
        kernel = clCreateKernel(program, "square", &err);
        if (!kernel || err != CL_SUCCESS)
        {
            printf("Error: Failed to create compute kernel!\n");
            exit(1);
        }

        // Create the input and output arrays in device memory for our calculation
        //
        input = clCreateBuffer(context,  CL_MEM_READ_ONLY,  sizeof(float) * count, NULL, NULL);
        output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * count, NULL, NULL);
        if (!input || !output)
        {
            printf("Error: Failed to allocate device memory!\n");
            exit(1);
        }    
        
        // Write our data set into the input array in device memory 
        //
        err = clEnqueueWriteBuffer(commands, input, CL_TRUE, 0, sizeof(float) * count, data, 0, NULL, NULL);
        if (err != CL_SUCCESS)
        {
            printf("Error: Failed to write to source array!\n");
            exit(1);
        }

        // Set the arguments to our compute kernel
        //
        err = 0;
        err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
        err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
        err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
        if (err != CL_SUCCESS)
        {
            printf("Error: Failed to set kernel arguments! %d\n", err);
            exit(1);
        }

        // Get the maximum work group size for executing the kernel on the device
        //
        err = clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
        if (err != CL_SUCCESS)
        {
            printf("Error: Failed to retrieve kernel work group info! %d\n", err);
            exit(1);
        }

        // Execute the kernel over the entire range of our 1d input data set
        // using the maximum number of work group items for this device
        //
        global = count;
        err = clEnqueueNDRangeKernel(commands, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
        if (err)
        {
            printf("Error: Failed to execute kernel!\n");
            return EXIT_FAILURE;
        }

        // Wait for the command commands to get serviced before reading back results
        //
        clFinish(commands);

        // Read back the results from the device to verify the output
        //
        err = clEnqueueReadBuffer( commands, output, CL_TRUE, 0, sizeof(float) * count, results, 0, NULL, NULL );  
        if (err != CL_SUCCESS)
        {
            printf("Error: Failed to read output array! %d\n", err);
            exit(1);
        }

        return 0;
    }

    OpenCL::~OpenCL()
    {
        delete[] this->current_kernel;

        clReleaseMemObject(input);
        clReleaseMemObject(output);
        clReleaseProgram(program);
        clReleaseKernel(kernel);
        clReleaseCommandQueue(commands);
        clReleaseContext(context);
    }
};