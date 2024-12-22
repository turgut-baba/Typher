/**
 * @file Engine.hpp
 * @author Turgut Bababalım (turgutbababalim@gmail.com)
 * @brief Entrance of my engine. 
 * @version 0.1
 * @date 2024-10-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef INFERENCE_ENGINE_HPP
#define INFERENCE_ENGINE_HPP

#include <vector>
#include <iostream>

namespace Typher{
    template<typename DataType>
    class Engine{
    public:
        Engine() = default;

        virtual void Run() = 0;

        virtual void load_model(std::string model_path) = 0;

        virtual void fill(std::vector<DataType>& input) = 0;

        virtual std::vector<DataType> get_output() = 0;

        virtual void set_gpu(bool gpu_switch) = 0;

        virtual ~Engine() = default;
    protected:
        bool filled = false;
        std::string model_path;
        std::vector<DataType> output;
    };
};

#endif