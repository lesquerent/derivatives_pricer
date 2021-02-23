#pragma once
#include"Option.h"
#include"BinLattice.h"
class PricerCrr
{
private:
    #pragma region Attributs
    double _underlyingPrice;//underlying price
    double _riskFreeRate; //interest rate

    double _upFactor; // prob to increase
    double _downFactor; // prob to decrease

    double _price; //price

    Option* _optionToCompute; //Pointer to the option to price
    BinLattice<double> _underlyingPricesVector; // Binomial tree containing the underlying prices for each period.
    BinLattice<double> _optionPricesVector; //Binomial tree containing the share prices at each period (used in case of US pricing type)
    BinLattice<double> _payOffVector; // Binomial tree containing the payoff of the action if executed at any time 

    std::string _typeFormula; // String containing the type of formula used. 
                              //At each pricing with a new formula the variable _typeFormula is modified to match the formula used to price.
    #pragma endregion

    /// <summary>
    /// Calculation of the factorial of the number passed in parameter
    /// </summary>
    /// <param name="number"></param>
    /// <returns></returns>
    static double factorial(int number);

public:
    /// <summary>
    /// Constructor, define à pricer CRR for the selectionned option
    /// </summary>
    /// <param name="option">Option to be price</param>
    /// <param name="underlyingPrice">The price of the option</param>
    /// <param name="riskFreeRate"></param>
    /// <param name="upFactor">Probability that the price of the underlying increase</param>
    /// <param name="downFactor">Probability that the price of the underlying decrease</param>
    PricerCrr(Option* option, double underlyingPrice, double riskFreeRate, double upFactor, double downFactor);
    /// <summary>
    /// Constructor, set a CRR pricer for the selected option
    /// Mainly used in order to use the CRR model as a black scholes limit
    /// </summary>
    /// <param name="option">Option to be price</param>
    /// <param name="underlyingPrice">The price of the option</param>
    /// <param name="riskFreeRate"></param>
    /// <param name="upFactor">Probability that the price of the underlying increase</param>
    /// <param name="downFactor">Probability that the price of the underlying decrease</param>
    PricerCrr(Option* option, double underlyingPrice, double riskFreeRate);
    ~PricerCrr();

    
    /// <summary>
    /// Price the option with the Closed Formula method
    /// </summary>
    /// <param name="nbSteps">: Number of steps in the tree</param>
    void pricingWithClosedFormFormula(int nbSteps);
    /// <summary>
    /// Price the option with the Closed Form Fomula method with Black Scholes as a limit.
    /// </summary>
    /// <param name="nbSteps">: Number of steps in the tree</param>
    /// <param name="volatility">: Underlying Volatility</param>
    void pricingWithClosedFormFormulaWithBlackScholesAsLimit(int nbSteps, double volatility);
    /// <summary>
    /// Price the option with the classic CRR method
    /// </summary>
    /// <param name="nbSteps">: Number of steps in the tree</param>
    /// <param name="us">: set as false by default, chose true if the pricing of the option requires a scalable calculation at each node as for an american option.</param>
    void pricingWithCrrModel(int nbSteps, bool us=false);
    /// <summary>
    /// Price the option with the classic CRR method  with Black Scholes as a limit
    /// </summary>
    /// <param name="nbSteps">: Number of steps in the tree</param>
    /// /// <param name="volatility">: Underlying Volatility</param>
    /// <param name="us">: set as false by default, chose true if the pricing of the option requires a scalable calculation at each node as for an american option</param>
    void pricingWithCrrModelWithBlackScholesAsLimit(int nbSteps, double volatility, bool us=false);
    /// <summary>
    /// Returns the binomial tree corresponding to the evolution of the prices.
    /// </summary>
    /// <returns></returns>
    BinLattice<double> getTreePrices();

    /// <summary>
    /// Returns the binomial tree corresponding to the evolution of the payoff.
    /// </summary>
    /// <returns></returns>
    BinLattice<double> getTreePayOff();
    /// <summary>
    /// Returns a string, including the price of the option and the type of formula used
    /// </summary>
    /// <returns></returns>
    std::string toString();
    
};

