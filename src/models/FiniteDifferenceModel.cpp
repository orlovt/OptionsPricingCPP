#include "models/FiniteDifferenceModel.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace Eigen;
using std::max;
using std::exp;

FiniteDifferenceModel::FiniteDifferenceModel(int timeSteps, int assetSteps) 
    : timeSteps_(timeSteps), assetSteps_(assetSteps) {}

double FiniteDifferenceModel::calculatePrice(const Option& option) const {

    return 0.0; // Placeholder
}
//     double T = option.getTimeToMaturity();
//     double S_0 = option.getSpotPrice();
//     double K = option.getStrikePrice();
//     double sigma = option.getVolatility();
//     double r = option.getRiskFreeRate();
//     std::string optionType = option.getType();

//     int N = timeSteps_;
//     int M = assetSteps_;
//     double S_max = 2 * K; // Assuming a maximum stock price
//     double dt = T / N;
//     double ds = S_max / M;

//     MatrixXd f = MatrixXd::Zero(M+1, N+1);

//     // Setting up boundary and final conditions based on option type
//     for (int i = 0; i <= M; ++i) {
//         double S = i * ds;
//         if (optionType == "call") {
//             f(i, N) = max(S - K, 0.0);
//         } else { // put
//             f(i, N) = max(K - S, 0.0);
//         }
//     }

//     for (int j = 0; j <= N; ++j) {
//         if (optionType == "call") {
//             f(0, j) = 0; // Call value when S=0
//             f(M, j) = max(S_max - K * exp(-r * (T - j * dt)), 0.0); // When S=S_max
//         } else { // put
//             f(0, j) = K * exp(-r * (T - j * dt)); // Put value when S=0
//             f(M, j) = 0; // Put value approaches 0 as S approaches S_max
//         }
//     }

//     // Coefficients for Crank-Nicolson
//     VectorXd alpha(M+1), beta(M+1), gamma(M+1);
//     for (int i = 0; i <= M; ++i) {
//         alpha(i) = 0.25 * dt * (sigma*sigma * i*i - r * i);
//         beta(i) = -dt * 0.5 * (sigma*sigma * i*i + r);
//         gamma(i) = 0.25 * dt * (sigma*sigma * i*i + r * i);
//     }

//     // Constructing matrices for Crank-Nicolson
//     MatrixXd A = MatrixXd::Zero(M-1, M-1);
//     MatrixXd B = MatrixXd::Zero(M-1, M-1);
//     for (int i = 0; i < M-1; ++i) {
//         A(i, i) = 1 - beta(i+1);
//         B(i, i) = 1 + beta(i+1);
//         if (i != M-2) {
//             A(i, i+1) = -gamma(i+1);
//             A(i+1, i) = -alpha(i+2);
//             B(i, i+1) = gamma(i+1);
//             B(i+1, i) = alpha(i+2);
//         }
//     }

//     // Backward solving using Crank-Nicolson
//     for (int j = N-1; j >= 0; --j) {
//         VectorXd b = VectorXd::Zero(M-1);
//         b(0) = alpha(1) * (f(0, j) + f(0, j+1));
//         b(M-2) = gamma(M-1) * (f(M, j) + f(M, j+1));
//         VectorXd y = B * f.block(1, j+1, M-1, 1) + b;
//         f.block(1, j, M-1, 1) = A.colPivHouseholderQr().solve(y);
//     }

//     // Interpolation for option price at S_0
//     double S_low = std::floor(S_0 / ds) * ds;
//     double S_high = std::ceil(S_0 / ds) * ds;
//     int index_low = S_low / ds;
//     int index_high = S_high / ds;
//     double price_low = f(index_low, 0);
//     double price_high = f(index_high, 0);
//     double price_S_0 = price_low + (S_0 - S_low) / (S_high - S_low) * (price_high - price_low);

//     return price_S_0;
// }
