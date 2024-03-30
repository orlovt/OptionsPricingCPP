#include "models/MonteCarloModel.hpp"
#include <omp.h>
#include <cmath>
#include <random>
#include <algorithm>

MonteCarloModel::MonteCarloModel(int numSimulations) : numSimulations_(numSimulations) {}

// Slower implementation 
// double MonteCarloModel::calculatePrice(const Option& option) const {
//     std::default_random_engine generator;
//     std::normal_distribution<double> distribution(0.0, 1.0);

//     double S = option.getSpotPrice();
//     double K = option.getStrikePrice();
//     double T = option.getTimeToMaturity();
//     double r = option.getRiskFreeRate();
//     double sigma = option.getVolatility();

//     double sumPayoff = 0.0;
//     for (int i = 0; i < numSimulations_; ++i) {
//         double Z = distribution(generator); // Random draw from a standard normal distribution
//         double St = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z); // Simulated asset price at maturity
//         double payoff = std::max(St - K, 0.0); // Payoff for a call option
//         sumPayoff += payoff;
//     }

//     double optionPrice = exp(-r * T) * (sumPayoff / numSimulations_); // Discounted average payoff
//     return optionPrice;
// }


double MonteCarloModel::calculatePrice(const Option& option) const {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    double S = option.getSpotPrice();
    double K = option.getStrikePrice();
    double T = option.getTimeToMaturity();
    double r = option.getRiskFreeRate();
    double sigma = option.getVolatility();
    
    double sumPayoff = 0.0;

    // Precomputing repeated terms
    double drift = exp((r - 0.5 * sigma * sigma) * T);
    double vol = sigma * sqrt(T);

    #pragma omp parallel for reduction(+:sumPayoff)
    for (int i = 0; i < numSimulations_; ++i) {
        double Z = distribution(generator); // Random draw
        double St = S * drift * exp(vol * Z); // Simulated price
        double payoff = std::max(St - K, 0.0);
        sumPayoff += payoff;
    }


    double optionPrice = exp(-r * T) * (sumPayoff / numSimulations_); // Discounted average payoff
    return optionPrice;
}