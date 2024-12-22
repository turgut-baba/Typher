project(Typher)

cmake_minimum_required(VERSION 3.0)

option(ONNXRUNTIME_ROOTDIR "onnxruntime root dir")

set(ONNXRUNTIME_ROOTDIR "/usr/lib/onnxruntime")

find_package(OpenCL REQUIRED)

include_directories("./include/")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

set(SOURCE
   ${SOURCE}
   ${SOURCE_DIR}/Gpu/OpenCL.cpp
   ${SOURCE_DIR}/Inference/Onnx.cpp
   ${SOURCE_DIR}/Utils/string_ops.cpp
   ${SOURCE_DIR}/Utils/file_ops.cpp

)

add_executable(
    Typher src/main.cpp ${SOURCE}
)

target_include_directories(
    Typher PRIVATE "${ONNXRUNTIME_ROOTDIR}/include"
                    "${ONNXRUNTIME_ROOTDIR}/include/onnxruntime"
                    "${ONNXRUNTIME_ROOTDIR}/include/onnxruntime/core/session"
)

target_link_directories(Typher PRIVATE "${ONNXRUNTIME_ROOTDIR}/build/Linux/RelWithDebInfo/")

target_link_libraries(Typher onnxruntime OpenCL::OpenCL)

set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 11
                                                 C_STANDARD_REQUIRED ON
                                                 C_EXTENSIONS OFF)

target_compile_definitions(${PROJECT_NAME} PRIVATE CL_TARGET_OPENCL_VERSION=100)