#include "models/BlackScholesModel.hpp"
#include <cmath>
#include <iostream>

BlackScholesModel::BlackScholesModel() {}

double BlackScholesModel::calculatePrice(const Option& option) const {
    double d1 = (log(option.getSpotPrice() / option.getStrikePrice()) +
                (option.getRiskFreeRate() + (option.getVolatility() * option.getVolatility()) / 2) * option.getTimeToMaturity()) /
                (option.getVolatility() * sqrt(option.getTimeToMaturity()));
    double d2 = d1 - option.getVolatility() * sqrt(option.getTimeToMaturity());

    if (option.getType() == "call") {
        return option.getSpotPrice() * normcdf(d1) - option.getStrikePrice() * exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normcdf(d2);
    } else if (option.getType() == "put") {
        return option.getStrikePrice() * exp(-option.getRiskFreeRate() * option.getTimeToMaturity()) * normcdf(-d2) - option.getSpotPrice() * normcdf(-d1);
    } else {
        std::cerr << "Invalid option type." << std::endl;
        return 0.0;
    }
}
