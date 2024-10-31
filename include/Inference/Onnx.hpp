/**
 * @file Onnx.hpp
 * @author Turgut Bababalım (turgutbababalim@gmail.com)
 * @brief Onnxruntime for inferance. 
 * @version 0.1
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef INFERENCE_ONNX_HPP
#define INFERENCE_ONNX_HPP

#include "Engine.hpp"
#include "Utils/string_ops.hpp"

#include <numeric>
#include <vector>
#include <onnxruntime_cxx_api.h>

class Onnx: public Engine<float>
{
public:
    explicit Onnx();

    void Run() override;

    void fill(std::vector<float>& input) override;

    std::vector<float> get_output() override;

    void set_gpu(bool gpu_switch) override;

    virtual ~Onnx() = default;
private:
    std::unique_ptr<Ort::Session> session;

    Ort::AllocatorWithDefaultOptions allocator;

    const char* inputName;
    std::vector<int64_t> inputDims;

    const char* outputName;
    std::vector<int64_t> outputDims;
};

#endif