#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>

class Option {
public:
    // Constructors
    Option(double spotPrice, double strikePrice, double riskFreeRate, double volatility, double timeToMaturity, const std::string& type);
    
    // Destructor
    virtual ~Option() = default;
    
    // Getter methods for option properties
    double getSpotPrice() const;
    double getStrikePrice() const;
    double getRiskFreeRate() const;
    double getVolatility() const;
    double getTimeToMaturity() const;
    std::string getType() const;

protected:
    double spotPrice_;
    double strikePrice_;
    double riskFreeRate_;
    double volatility_;
    double timeToMaturity_;
    std::string type_; // "call" or "put"
};

#endif // OPTION_HPP
