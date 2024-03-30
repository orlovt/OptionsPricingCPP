#include "Factory/PricingModelFactory.hpp"
#include "domain/Option.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <chrono> 
#include <cstdlib> // For std::stod

int main(int argc, char* argv[]) {
    
    // Default option parameters
    double spotPrice = 100.0;
    double strikePrice = 100.0;
    double riskFreeRate = 0.1;
    double volatility = 0.1;
    double timeToMaturity = 1.0;
    std::string optionType = "call";

    // Check if input arguments are provided
    if (argc > 6) { // Expecting 6 arguments: executable name, spotPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, optionType
        try {
            spotPrice = std::stod(argv[1]);
            strikePrice = std::stod(argv[2]);
            riskFreeRate = std::stod(argv[3]);
            volatility = std::stod(argv[4]);
            timeToMaturity = std::stod(argv[5]);
            optionType = argv[6];
        } catch (const std::exception& e) {
            std::cerr << "Error parsing input arguments: " << e.what() << std::endl;
            return 1; // Exit with error code
        }
    }

    // Create an Option object
    Option option(spotPrice, strikePrice, riskFreeRate, volatility, timeToMaturity, optionType);

    // List of pricing models to use
    std::vector<std::string> models = {"Binomial", "BlackScholes", "MonteCarlo"};

    // Loop through each model, calculate prices, and time the operation
    for (const auto& modelName : models) {
        auto model = PricingModelFactory::createModel(modelName);
        if (model) {
            auto start = std::chrono::high_resolution_clock::now(); // Start timing
            
            double price = model->calculatePrice(option); // Pricing calculation
            
            auto end = std::chrono::high_resolution_clock::now(); // End timing
            std::chrono::duration<double, std::milli> duration = end - start; // Calculate duration
            
            std::cout << modelName << ":\t " << price << " \t(Time: " << duration.count() << " ms)" << std::endl;
        } else {
            std::cerr << "Failed to create " << modelName << " pricing model." << std::endl;
        }
    }

    return 0;
}
