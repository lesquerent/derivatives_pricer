#include "PricerMonteCarlo.h"

//Private Method

double PricerMonteCarlo::estimatedPrice(double previousPrice, double riskFreeRate, double volatility, double deltaT) {

    return previousPrice * exp(((riskFreeRate - ((volatility * volatility) / 2)) * deltaT) + (volatility * sqrt(deltaT) * normalDistribution(0, 1)));
}
double PricerMonteCarlo::normalDistribution(double mean, double stdDev) {

    SingletonMersenTwister& mersen_instance = SingletonMersenTwister::getInstance();
    std::normal_distribution<double> dis(mean, stdDev);
    return dis(mersen_instance.gen);
}
double PricerMonteCarlo::calculError(int percent = 95)
{
    double q = 0.0;
    double erreur;

    //Compute de variance of the estimator
    double var = _meanSquare - (_meanSample * _meanSample);

    //Switch case on differents percent of confidence
    switch (percent)
    {
    case 99:
        q = 2.5758;
        erreur = q * sqrt(var / _nbSequencesTotal);
        break;

    case 90:
        q = 1.6449;
        erreur = q * sqrt(var / _nbSequencesTotal);
        break;

    default: //95%
        q = 1.9600;
        erreur = q * sqrt(var / _nbSequencesTotal);
        break;
    }
    //Return the error price - (mean - error) actualised to today
    return abs(_price - ((_meanSample - erreur) * exp(-_riskFreeRate * _optionToCompute->getMaturity())));
}

//Public Method

PricerMonteCarlo::PricerMonteCarlo(Option* option, double underlyingPrice, double riskFreeRate, double volatility, int nbPath, int nbSequences)
{
    _optionToCompute = option;
    _underlyingPrice = underlyingPrice;
    _riskFreeRate = riskFreeRate;
    _nbPath = nbPath;
    _nbSequencesTotal = nbSequences;
    _nbSequences = nbSequences;
    _volatility = volatility;
    _price = NULL;
    _meanSample = NULL;
    _meanSquare = NULL;
}
PricerMonteCarlo::~PricerMonteCarlo()
{
}
double PricerMonteCarlo::pricinWithMonteCarloMethod()
{
    double maturity = _optionToCompute->getMaturity();
    double optionPrice = 0;
    double deltaT = maturity / _nbPath;

    std::vector<std::vector<double>> vectorOfEstimatedPrices;
    //Vector resizing: would contain _nbSequences vectors
    vectorOfEstimatedPrices.resize(_nbSequences);

    //Vector resizing corresponding to the nb-th step (ex: vectorOfEstimatedPrices[0].size = 1, vectorOfEstimatedPrices[1].size = 2, vectorOfEstimatedPrices[4].size = 5)
    for (int i = 0;i <= _nbSequences - 1;i++) {
        vectorOfEstimatedPrices[i].resize(_nbPath + 1);
    }

    //Set the first price to the underlying price at t=0
    for (int i = 0;i <= _nbSequences - 1;i++) {
        vectorOfEstimatedPrices[i][0] = _underlyingPrice;
    }

    //Fill the vectorOfEstimatedPrices with prices following the monte carlo random path method
    for (int i = 0;i <= _nbSequences - 1;i++) {
        for (int j = 1;j <= _nbPath;j++) {
            double estimationPrice = estimatedPrice(vectorOfEstimatedPrices[i][j - 1], _riskFreeRate, _volatility, deltaT);
            vectorOfEstimatedPrices[i][j] = estimationPrice;

        }
    }

    //set a tuple wich contain the mean and mean squared
     std::tuple<double, double> meanMeanSquared = _optionToCompute->meanMeanSquaredPayOff(vectorOfEstimatedPrices);

    
    //If we don't have ever price this model : (useful when you want to improve the estimate).
    if (_meanSample == NULL) {
        _meanSample =  std::get<0>(meanMeanSquared);
        _meanSquare =  std::get<1>(meanMeanSquared);
    }
    //If we have already price this model, then we refine the estimate :
    else {
        _meanSample = (_meanSample + std::get<0>(meanMeanSquared))/2;
        _meanSquare = (_meanSquare + std::get<1>(meanMeanSquared))/2;
    }

    optionPrice = exp(-_riskFreeRate * maturity) * _meanSample;
    _price = optionPrice;
    return _price;
    
}
std::string PricerMonteCarlo::toString()
{
    return std::to_string(_price) + " with the " + std::to_string(_nbSequencesTotal) + " sequences of prices.";
}
std::string PricerMonteCarlo::toString(int percent)
{
    return std::to_string(_price) + " with Monte Carlo with " + std::to_string(_nbSequencesTotal) + " sequences of prices with interval of confidence at "+std::to_string(percent) + "% [ " + std::to_string(_price) + " +- " + std::to_string(calculError(percent)) + " ]\n";
}
std::string PricerMonteCarlo::getConfidenceInterval(int percent)
{
    std::string interval = "[ " + std::to_string(_price) + " +- " + std::to_string(calculError(percent)) + " ]";
    return interval;   
}
void PricerMonteCarlo::refines(int nbSequences)
{
    _nbSequences = nbSequences;
    _nbSequencesTotal += nbSequences;
    this->pricinWithMonteCarloMethod();
}