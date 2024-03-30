// PricingModelFactory.hpp

#ifndef PRICING_MODEL_FACTORY_HPP
#define PRICING_MODEL_FACTORY_HPP

#include "models/OptionPricingModel.hpp"
#include <memory>
#include <string>

class PricingModelFactory {
public:
    static std::unique_ptr<OptionPricingModel> createModel(const std::string& modelName);
};

#endif // PRICING_MODEL_FACTORY_HPP