#ifndef MONTE_CARLO_MODEL_HPP
#define MONTE_CARLO_MODEL_HPP

#include "models/OptionPricingModel.hpp"
#include "domain/Option.hpp"

class MonteCarloModel : public OptionPricingModel {
public:
    MonteCarloModel(int numSimulations = 10000);
    virtual double calculatePrice(const Option& option) const override;

private:
    int numSimulations_; // Number of simulated asset paths
};

#endif // MONTE_CARLO_MODEL_HPP
