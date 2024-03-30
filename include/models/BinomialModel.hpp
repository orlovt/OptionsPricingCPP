#ifndef BINOMIAL_MODEL_HPP
#define BINOMIAL_MODEL_HPP

#include "models/OptionPricingModel.hpp"
#include "domain/Option.hpp"

class BinomialModel : public OptionPricingModel {
public:
    BinomialModel();
    virtual double calculatePrice(const Option& option) const override;
};

#endif // BINOMIAL_MODEL_HPP
