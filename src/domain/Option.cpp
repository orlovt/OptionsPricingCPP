#include "domain/Option.hpp"

// Constructor implementation
Option::Option(double spotPrice, double strikePrice, double riskFreeRate, double volatility, double timeToMaturity, const std::string& type)
    : spotPrice_(spotPrice), strikePrice_(strikePrice), riskFreeRate_(riskFreeRate), volatility_(volatility), timeToMaturity_(timeToMaturity), type_(type) {}

// Getter method implementations
double Option::getSpotPrice() const {
    return spotPrice_;
}

double Option::getStrikePrice() const {
    return strikePrice_;
}

double Option::getRiskFreeRate() const {
    return riskFreeRate_;
}

double Option::getVolatility() const {
    return volatility_;
}

double Option::getTimeToMaturity() const {
    return timeToMaturity_;
}

std::string Option::getType() const {
    return type_;
}
