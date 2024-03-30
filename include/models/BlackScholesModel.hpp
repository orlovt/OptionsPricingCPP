#ifndef BLACK_SCHOLES_MODEL_HPP
#define BLACK_SCHOLES_MODEL_HPP

#include "domain/Option.hpp"
#include "models/OptionPricingModel.hpp"
#include "util/MathHelpers.hpp"
#include <string>

class BlackScholesModel : public OptionPricingModel {
public:
    BlackScholesModel();
    virtual double calculatePrice(const Option& option) const override;
};

#endif // BLACK_SCHOLES_MODEL_HPP
