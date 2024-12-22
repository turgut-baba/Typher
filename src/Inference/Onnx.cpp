/**
 * @file Onnx.cpp
 * @author Turgut Bababalım (turgutbababalim@gmail.com)
 * @brief Onnxruntime for inferance. 
 * @version 0.1
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Inference/Onnx.hpp"

namespace Typher{
    template <typename T>
    T vectorProduct(const std::vector<T>& v)
    {
        return accumulate(v.begin(), v.end(), 1, std::multiplies<T>());
    }

    Onnx::Onnx(std::string& model_path) // "image-classification-inference"
    {
        Ort::Env env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING,
                    "Typher-Instance");

        Ort::SessionOptions sessionOptions;
        sessionOptions.SetIntraOpNumThreads(1);

        sessionOptions.SetGraphOptimizationLevel(
            GraphOptimizationLevel::ORT_DISABLE_ALL);

        if(!checkModelExtension(model_path)) 
        {
            throw std::runtime_error("[ ERROR ] The ModelFilepath is not correct. Make sure you are setting the path to an onnx model file (.onnx)");
        }

        session = std::make_unique<Ort::Session>(env, model_path.c_str(), sessionOptions);

        size_t numInputNodes = session->GetInputCount();
        size_t numOutputNodes = session->GetOutputCount();
    }

    void Onnx::load_model(std::string model_path)
    {
        // TODO: research and propperly implement this. 
    }

    void Onnx::fill(std::vector<float>& input)
    {
        auto inputNodeName = session->GetInputNameAllocated(0, allocator);
        inputName = inputNodeName.get();
        std::cout << "Input Name: " << inputName << std::endl;

        Ort::TypeInfo inputTypeInfo = session->GetInputTypeInfo(0);
        auto inputTensorInfo = inputTypeInfo.GetTensorTypeAndShapeInfo();

        ONNXTensorElementDataType inputType = inputTensorInfo.GetElementType();
        std::cout << "Input Type: " << inputType << std::endl;

        inputDims = inputTensorInfo.GetShape();


        auto outputNodeName = session->GetOutputNameAllocated(0, allocator);
        outputName = outputNodeName.get();

        Ort::TypeInfo outputTypeInfo = session->GetOutputTypeInfo(0);
        auto outputTensorInfo = outputTypeInfo.GetTensorTypeAndShapeInfo();

        ONNXTensorElementDataType outputType = outputTensorInfo.GetElementType();

        outputDims = outputTensorInfo.GetShape();
    }

    void Onnx::Run()
    {
        size_t inputTensorSize = vectorProduct(inputDims);

        std::vector<float> inputTensorValues(inputTensorSize);

    /*     inputTensorValues.assign(preprocessedImage.begin<float>(),
                                preprocessedImage.end<float>()); */

        size_t outputTensorSize = vectorProduct(outputDims);

        std::vector<float> outputTensorValues(outputTensorSize);


        /* Once the buffers were created, they would be used for creating instances of Ort::Value 
        which is the tensor format for ONNX Runtime. There could be multiple inputs for a neural network, 
        so we have to prepare an array of Ort::Value instances for inputs and outputs respectively even if 
        we only have one input and one output. */

        std::vector<const char*> inputNames{inputName};
        std::vector<const char*> outputNames{outputName};
        std::vector<Ort::Value> inputTensors;
        std::vector<Ort::Value> outputTensors;

        /*
        Creating ONNX Runtime inference sessions, querying input and output names, 
        dimensions, and types are trivial.
        Setup inputs & outputs: The input & output tensors are created here. */

        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(
            OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeDefault);

        inputTensors.push_back(Ort::Value::CreateTensor<float>(
            memoryInfo, inputTensorValues.data(), inputTensorSize, inputDims.data(),
            inputDims.size()));
            
        outputTensors.push_back(Ort::Value::CreateTensor<float>(
            memoryInfo, outputTensorValues.data(), outputTensorSize,
            outputDims.data(), outputDims.size()));

        /* To run inference, we provide the run options, an array of input names corresponding to the 
        inputs in the input tensor, an array of input tensor, number of inputs, an array of output names 
        corresponding to the the outputs in the output tensor, an array of output tensor, number of outputs. */

        session->Run(Ort::RunOptions{nullptr}, inputNames.data(),
                    inputTensors.data(), 1, outputNames.data(),
                    outputTensors.data(), 1);
    }

    std::vector<float> Onnx::get_output() 
    {
        
    }

    void Onnx::set_gpu(bool gpu_switch)
    {

    }
};