#include "models/BinomialModel.hpp"
#include <vector>
#include <cmath>
#include <algorithm> 

BinomialModel::BinomialModel() {}

// double BinomialModel::calculatePrice(const Option& option) const {
//     const int steps = 12; // Hardcoded steps for monthly intervals
//     double expiry = option.getTimeToMaturity();
//     double annualVolatility = option.getVolatility();
//     double riskFreeRate = option.getRiskFreeRate();
//     double S = option.getSpotPrice();
//     double K = option.getStrikePrice();

//     // Calculate time per step, in years
//     double deltaT = expiry / steps;
//     // Adjust volatility for monthly steps
//     double monthlyVolatility = annualVolatility / sqrt(12);

//     // Cox-Ross-Rubinstein model parameters for monthly steps
//     double upFactor = exp(monthlyVolatility * sqrt(deltaT));
//     double downFactor = 1 / upFactor;
//     double riskNeutralProb = (exp(riskFreeRate * deltaT) - downFactor) / (upFactor - downFactor);

//     double optionPrice = 0.0;
//     for (int i = 0; i <= steps; ++i) {
//         double stockPriceAtNode = S * pow(upFactor, i) * pow(downFactor, steps - i);
//         double payoff = 0;
//         if (option.getType() == "call") {
//             payoff = std::max(stockPriceAtNode - K, 0.0);
//         } else { // put
//             payoff = std::max(K - stockPriceAtNode, 0.0);
//         }
//         double binomialCoefficient = tgamma(steps + 1) / (tgamma(i + 1) * tgamma(steps - i + 1));
//         optionPrice += binomialCoefficient * pow(riskNeutralProb, i) * pow(1 - riskNeutralProb, steps - i) * payoff;
//     }

//     // Discount back to present value
//     optionPrice *= exp(-riskFreeRate * expiry);

//     return optionPrice;
// }




double BinomialModel::calculatePrice(const Option& option) const {
    const int steps = 12; // Number of steps in the binomial tree
    const double S = option.getSpotPrice(); // Current stock price
    const double K = option.getStrikePrice(); // Strike price
    const double T = option.getTimeToMaturity(); // Time to maturity
    const double r = option.getRiskFreeRate(); // Risk-free rate
    const double sigma = option.getVolatility(); // Volatility
    const std::string optionType = option.getType(); // "call" or "put"

    // Calculate the up and down factors and the risk-neutral probability
    const double dt = T / steps; // Time step
    const double u = exp(sigma * sqrt(dt));
    const double d = 1 / u;
    const double q = (exp(r * dt) - d) / (u - d); // Risk-neutral probability

    // Pre-compute powers of up and down factors and probabilities
    std::vector<double> upPowers(steps + 1), downPowers(steps + 1);
    upPowers[0] = downPowers[0] = 1.0; // u^0 and d^0
    for (int i = 1; i <= steps; ++i) {
        upPowers[i] = upPowers[i-1] * u;
        downPowers[i] = downPowers[i-1] * d;
    }

    // Initialize option values at terminal nodes
    std::vector<double> optionValuesAtTerminal(steps + 1);
    for (int i = 0; i <= steps; ++i) {
        double stockPriceAtNode = S * upPowers[i] * downPowers[steps - i];
        if (optionType == "call") {
            optionValuesAtTerminal[i] = std::max(stockPriceAtNode - K, 0.0);
        } else { // put
            optionValuesAtTerminal[i] = std::max(K - stockPriceAtNode, 0.0);
        }
    }

    // Dynamic programming to fill the option price tree backward
    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            optionValuesAtTerminal[i] = exp(-r * dt) * (q * optionValuesAtTerminal[i + 1] + (1 - q) * optionValuesAtTerminal[i]);
        }
    }

    return optionValuesAtTerminal[0];
}
