#pragma once
#include <iostream>
#include "SingletonMersenTwister.h"
#include <random>
#include "Option.h"
#include "BinLattice.h"

class PricerMonteCarlo
{
private:
    #pragma region Attributs
    double _underlyingPrice;//underlying price
    double _riskFreeRate; //interest rate

    double _volatility;

    double _meanSquare;// Mean of the payoff squares, used to calculate the confidence interval
    double _meanSample;// Mean of the payoff, used to calculate the confidence interval

    int _nbPath; //number of iterations before maturity
    int _nbSequences; //number of sequences of prices
    int _nbSequencesTotal; //number of sequences of prices

    double _price; //prix

    Option* _optionToCompute; //Pointer to the option to price
    std::vector<std::vector<double>> _vectorOfEstimatedPrices; //table to contain all random price sequences

    
    #pragma endregion   

    /// <summary>
    /// Function that return a price based on the random process for the monte carlo model
    /// </summary>
    /// <param name="previousPrice">Price at t-1</param>
    /// <param name="riskFreeRate">Risk free rate</param>
    /// <param name="volatility">Volatility of the underlying</param>
    /// <param name="deltaT">T/nbStep, the distance of a path</param>
    /// <returns>estimated price</returns>
    static double estimatedPrice(double previousPrice, double riskFreeRate, double volatility, double deltaT);
    /// <summary>
    /// Return a random variable with a Normale Distribution
    /// </summary>
    /// <param name="mean">mean of the normale distribution</param>
    /// <param name="stdDev"> standard deviation of the distribution</param>
    /// <returns></returns>
    static double normalDistribution(double mean, double stdDev);
    /// <summary>
    /// Calculate the error of the estimator only for 99%, 90% and 95% which is the default calculation, for all other values we return for 95%.
    /// </summary>
    /// <param name="percent"></param>
    /// <returns></returns>
    double calculError(int percent);

public:

    /// <summary>
    /// Constructor, define a monte carlo pricer model for an underlying
    /// </summary>
    /// <param name="option"></param>
    /// <param name="underlyingPrice"></param>
    /// <param name="riskFreeRate"></param>
    /// <param name="volatility"></param>
    /// <param name="nbPath"></param>
    /// <param name="nbSequences"></param>
    PricerMonteCarlo(Option* option, double underlyingPrice, double riskFreeRate,double volatility, int nbPath, int nbSequences);
    ~PricerMonteCarlo();
    /// <summary>
    /// Price the option with the Monte Carlo Random Path Model, retun the price and also stock it in the price attribut of the model
    /// </summary>
    /// <returns>The price of the option</returns>
    double pricinWithMonteCarloMethod();
    /// <summary>
    /// Return a string with the estimation of price and the number of sequences used for obtain this price
    /// </summary>
    /// <returns></returns>
    std::string toString();
    /// <summary>
    /// Return a string with the estimation of price, the number of sequences used for obtain this price and the interval of confidence
    /// </summary>
    /// <param name="percent">Percentage for the interval of confidence (90,95 or 99)</param>
    /// <returns></returns>
    std::string toString(int percent);
    /// <summary>
    /// Return the interval of confidence obtain this price 
    /// </summary>
    /// <param name="percent">Percentage for the interval of confidence (90,95 or 99)</param>
    /// <returns></returns>
    std::string getConfidenceInterval(int percent);
    /// <summary>
    /// Refines the estimator of the option pric
    /// </summary>
    /// <param name="nbSequences">The number of sequences of prices that we want to add</param>
    void refines(int nbSequences);
};

