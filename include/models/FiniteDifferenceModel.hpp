#ifndef FINITE_DIFFERENCE_MODEL_HPP
#define FINITE_DIFFERENCE_MODEL_HPP

#include "models/OptionPricingModel.hpp"
#include "domain/Option.hpp"

class FiniteDifferenceModel : public OptionPricingModel {
public:
    FiniteDifferenceModel(int timeSteps = 100, int assetSteps = 100);
    virtual double calculatePrice(const Option& option) const override;

private:
    int timeSteps_;   // Number of time steps in the grid
    int assetSteps_;  // Number of asset price steps in the grid
};

#endif // FINITE_DIFFERENCE_MODEL_HPP
