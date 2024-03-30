// PricingModelFactory.cpp

#include "Factory/PricingModelFactory.hpp"
#include "models/BlackScholesModel.hpp" 
#include "models/BinomialModel.hpp" 
#include "models/MonteCarloModel.hpp" 
#include "models/FiniteDifferenceModel.hpp" 
#include <stdexcept>
// Include other models as needed

std::unique_ptr<OptionPricingModel> PricingModelFactory::createModel(const std::string& modelName) {
    if (modelName == "BlackScholes") {
        return std::make_unique<BlackScholesModel>();
    } else if (modelName == "Binomial") {
        return std::make_unique<BinomialModel>(); // Return an instance of the Binomial model
    } else if (modelName == "MonteCarlo") {
        return std::make_unique<MonteCarloModel>(); // Return an instance of the Binomial model
    } else if (modelName == "FiniteDifference") {
        return std::make_unique<FiniteDifferenceModel>(); // Return an instance of the Binomial model
    }

    // If no model matches, return nullptr or throw an exception
    throw std::runtime_error("Unknown model name");
}
