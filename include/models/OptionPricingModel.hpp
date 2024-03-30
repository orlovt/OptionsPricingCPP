#ifndef OPTION_PRICING_MODEL_HPP
#define OPTION_PRICING_MODEL_HPP

#include "domain/Option.hpp"

class OptionPricingModel {
public:
    virtual ~OptionPricingModel() = default;
    virtual double calculatePrice(const Option& option) const = 0;
};

#endif // OPTION_PRICING_MODEL_HPP
