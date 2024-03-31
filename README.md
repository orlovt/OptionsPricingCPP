# Options Pricing in C++

## Overview
This project implements several fundamental options pricing models in C++, offering a comprehensive toolkit for financial analysis and research. The models included are the Black-Scholes model, the Binomial model, the Finite Difference Method (FDM), and the Monte Carlo simulation method. Each model has been encapsulated within its own class, following object-oriented programming principles, to provide a clear, modular, and extensible architecture that can be easily expanded with new pricing models.

## Installation

To compile and run the project, ensure you have a C++ compiler and make installed on your system. The project is structured to use a Makefile for easy compilation.

```bash
# Clone the repository
git clone https://github.com/orlovt/OptionsPricingCPP.git

# Navigate to the project directory
cd OptionsPricingCPP

# Compile the project
make

# Execute the program
./price_opt

# Or execute with args spotPrice, strikePrice, rfRate, annualizedVolatility, timeToMaturity, optionType 
./price_opt 100.00 100.00 0.1 0.1 1.0 call
```

## Usage

The executable `price_opt` provides a command-line interface to select and run different pricing models with predefined or user-specified parameters.

```bash
# Example usage
./price_opt 100.00 100.00 0.1 0.1 1.0 call
```

Replace the parameters with your desired values to compute the price of an option using the selected model.

## Performance Comparison and Improvement


| Pricing Model  | Initial Time (ms) | Optimized Time (ms) | Improvement |
|----------------|-------------------|---------------------|-------------|
| Binomial       | 0.013708          | 0.008734            | ~36.3%      |
| Black-Scholes  | 0.001708          | 0.000508            | ~70.3%      |
| Monte Carlo    | 2.72567           | 0.596726            | ~78.1%      |


- The **Binomial model** saw a reduction in execution time by approximately 36%, highlighting the impact of optimized tree traversal and usage of dynamic programing techniques, which has let to cut the number of expencive computations.
- The **Black-Scholes model** achieved a execution time reduction of around 70%, benefiting from optimized mathematical computations, more efficient library calls and compiler changes.
- The **Monte Carlo model** exhibited the most significant improvement with a reduction in execution time by over 78%, which can be attributed to optimized random number generation, parallelization of simulations, and variance reduction techniques.


## Project Structure

- `Makefile`: Contains rules for compiling the project.
- `include/`: Header files for the project.
  - `Factory/`: Contains the `PricingModelFactory` for creating model instances.
  - `domain/`: Domain-specific classes, like `Option`.
  - `models/`: Pricing models implementations.
  - `util/`: Utility functions and helpers, such as mathematical functions.
- `src/`: Source files mirroring the structure in `include/`.
<details>
<summary><h2>Pricing Models</h2> (click to expand)</summary>


### [Black-Scholes Model](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://en.wikipedia.org/wiki/Black%25E2%2580%2593Scholes_model&ved=2ahUKEwjQkuyalZ2FAxXltokEHTxTCxwQFnoECCkQAQ&usg=AOvVaw3Y3P-LHLGDz-OHGgwisPKx)

The Black-Scholes model provides a closed-form solution for pricing European call and put options. It assumes a constant volatility and risk-free rate.

**Call Option Price $`C(S, T)`$**
$$C(S, T) = S_0 \cdot N(d_1) - K \cdot e^{-rT} \cdot N(d_2)$$

**Put Option Price $`P(S, T)`$**
$$P(S, T) = K \cdot e^{-rT} \cdot N(-d_2) - S_0 \cdot N(-d_1)$$

where:
- $` S_0 `$ is the current stock price,
- $` K `$ is the strike price,
- $` T `$ is the time to expiration (in years),
- $` r `$ is the risk-free interest rate (annual rate, expressed in terms of continuous compounding),
- $` \sigma `$ is the volatility of the stock price (standard deviation of the stock's returns),
- $` N(\cdot) `$ is the cumulative distribution function of the standard normal distribution,

and $` d_1 `$ and $` d_2 `$ are calculated as follows:

$$d_1 = \frac{\ln(\frac{S_0}{K}) + (r + \frac{\sigma^2}{2})T}{\sigma\sqrt{T}}$$

$$d_2 = d_1 - \sigma\sqrt{T}$$


### [Binomial Model](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://en.wikipedia.org/wiki/Binomial_options_pricing_model&ved=2ahUKEwjw98z1np2FAxVnhIkEHT4SCjcQFnoECDMQAQ&usg=AOvVaw17PuzsxohClPB-jfpTJb4j)
The Binomial model prices options by constructing a binomial tree to model the underlying's price movements, allowing for the pricing of American options.


1. **Step Size**: The time to expiration $` T `$ is divided into $` N `$ equal intervals of length $` \Delta t = \frac{T}{N} `$.

2. **Up and Down Factors**: The model calculates the up ($` u `$) and down ($` d `$) factors, which represent the possible price changes in one step.
$$u = e^{\sigma \sqrt{\Delta t}}$$
$$d = e^{-\sigma \sqrt{\Delta t}}$$
where $` \sigma `$ is the volatility of the underlying asset.

4. **Risk-neutral Probability**: The model uses a risk-neutral probability ($` q `$) for the price moving up, calculated as:
$$q = \frac{e^{r\Delta t} - d}{u - d}$$
where $` r `$ is the risk-free interest rate.

**Formulas for Option Valuation**

The value of a European call or put option at each node is calculated using the formula:
$$C = e^{-r\Delta t} [qC_u + (1 - q)C_d]$$
$$P = e^{-r\Delta t} [qP_u + (1 - q)P_d]$$
where $` C_u `$ and $` C_d `$ (or $` P_u `$ and $` P_d `$) are the values of the call (or put) option in the next step if the price moves up or down, respectively.


### [Finite Difference Method (FDM)](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://en.wikipedia.org/wiki/Finite_difference_methods_for_option_pricing%23:~:text%3DIn%2520general%252C%2520finite%2520difference%2520methods,discrete%252Dtime%2520difference%2520equations.&ved=2ahUKEwi-_s3_np2FAxUoDHkGHZX7BGQQFnoECBAQAw&usg=AOvVaw1MG5Om0CMwisOsxdIRuGzJ)
The FDM solves the Black-Scholes PDE numerically using a discretized grid over asset prices and time, applicable to various boundary conditions.


1. **Grid Construction**: Create a grid over the domain of interest, typically the range of possible underlying asset prices and time until expiration. The grid is defined by intervals $` \Delta S `$ for the asset price and $` \Delta t `$ for time.

2. **Discretization of the PDE**: The continuous PDE is approximated by finite differences. The choice of discretization scheme (explicit, implicit, or Crank-Nicolson) affects the stability and accuracy of the solution.

3. **Initial and Boundary Conditions**: Apply the initial condition, typically the option's payoff at expiration, and boundary conditions reflecting the option's behavior as the asset price approaches zero or infinity.

4. **Backward in Time Solution**: Solve the discretized equations backward in time from the known final conditions at expiration to obtain the option's price at the desired earlier time.

**Fundamental Equations**

The PDE for a vanilla European option under the Black-Scholes framework is:
$$\frac{\partial V}{\partial t} + \frac{1}{2} \sigma^2 S^2 \frac{\partial^2 V}{\partial S^2} + rS\frac{\partial V}{\partial S} - rV = 0$$

Where:
- $` V `$ is the option price,
- $` S `$ is the underlying asset price,
- $` t `$ is time,
- $` \sigma `$ is the volatility of the underlying asset,
- $` r `$ is the risk-free interest rate.

**Discretization Example (Explicit Scheme)**
The time derivative can be approximated by a forward difference and the second spatial derivative by a central difference:
$$\frac{V^{i+1}_j - V^i_j}{\Delta t} + \frac{1}{2} \sigma^2 S_j^2 \frac{V^i_{j+1} - 2V^i_j + V^i_{j-1}}{\Delta S^2} + rS_j\frac{V^i_{j+1} - V^i_{j-1}}{2\Delta S} - rV^i_j = 0$$



### [Monte Carlo Simulation](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://en.wikipedia.org/wiki/Monte_Carlo_methods_for_option_pricing&ved=2ahUKEwj-jPGGn52FAxUjmIkEHbkXCYIQFnoECCQQAQ&usg=AOvVaw2uPIKtB2xjy9roK_KgQuZT)
Monte Carlo simulation estimates the price of an option by simulating the underlying asset's price path multiple times and calculating the average outcome.


$$dS_t = \mu S_t dt + \sigma S_t dW_t$$

where:
- $` S_t `$ is the price of the asset at time $` t `$,
- $` \mu `$ is the expected return (drift) of the asset,
- $` \sigma `$ is the volatility (standard deviation) of the asset's returns,
- $` dW_t `$ is the increment of a Wiener process (Brownian motion), representing random fluctuations.

**Simulation of Price Paths**

To simulate the future price of an asset under the GBM model, the discrete counterpart of the SDE over a small time interval $` \Delta t `$ is used:

$$S_{t+\Delta t} = S_t \exp\left((\mu - \frac{1}{2}\sigma^2)\Delta t + \sigma\sqrt{\Delta t}Z\right)$$

where $` Z `$ is a random draw from the standard normal distribution $` N(0,1) `$.

**Option Payoff Calculation**

For each simulated path of the underlying asset, the payoff of the option is calculated based on the option type. For example, for a European call option, the payoff at maturity $` T `$ is:

$$\text{Payoff} = \max(S_T - K, 0)$$

and for a European put option:

$$\text{Payoff} = \max(K - S_T, 0)$$

where $` S_T `$ is the simulated price of the underlying asset at maturity and $` K `$ is the strike price of the option.

**Discounting to Present Value**

The expected payoff of the option is computed by averaging the payoffs of all simulated paths. This average is then discounted back to the present value using the risk-free interest rate $` r `$, to get the option's price:

$$\text{Option Price} = e^{-rT} \times \frac{1}{N} \sum_{i=1}^{N} \text{Payoff}_i$$

where $` N `$ is the number of simulated paths.
</details>
  
## License

This project is licensed under the MIT License - see the LICENSE.md file for details.

