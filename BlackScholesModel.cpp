#include "BlackScholesModel.h"
#include <sstream>
#include <math.h>



//Private method

// Returns the erf() of a value (not super precice, but ok)
double BlackScholesModel::erf(double x)
{
    double y = 1.0 / (1.0 + 0.3275911 * x);
    return 1 - (((((
        +1.061405429 * y
        - 1.453152027) * y
        + 1.421413741) * y
        - 0.284496736) * y
        + 0.254829592) * y)
        * exp(-x * x);
}
// Returns the probability of [-inf,x] of a gaussian distribution
double BlackScholesModel::cdf(double x, double mo = 0, double sigmo = 1)
{
    return 0.5 * (1 + erf((x - mo) / (sigmo * sqrt(2.))));
}


//Public method
BlackScholesModel::BlackScholesModel(Option* optionToCompute, double underlyingPrice, double riskFreeRate, double volatility)
{
    _optionToCompute = optionToCompute;
    _underlyingPrice = underlyingPrice;
    _riskFreeRate = riskFreeRate;
    _volatility = volatility;
    _price = NULL;
    _delta = NULL;
}
BlackScholesModel::~BlackScholesModel() {}
void BlackScholesModel::pricingWithBlackSholesModel()
{
    // Attribut de l'option
    TypeOption type = _optionToCompute->getType();
    double strikePrice = _optionToCompute->getStrikePrice();
    double maturity = _optionToCompute->getMaturity();
    

    // Calcul de d1 et d2 pour effectuer la méthode de Black-Scholes
    double d1 = (log2(_underlyingPrice / strikePrice) + maturity*((_riskFreeRate + (0.5 * _volatility * _volatility)) )) / (_volatility * sqrt(maturity));
    double d2 = d1 - (_volatility * sqrt(maturity));
   
    switch (type)
    {
    case TypeOption::call:
        _price = (_underlyingPrice * cdf(d1,0,1)) - (strikePrice * exp(-_riskFreeRate * (maturity)) * cdf(d2,0,1));
        _delta = cdf(d1,0,1);
        break;
    case TypeOption::put:
        
        _price = strikePrice * exp(-_riskFreeRate * (maturity)) * cdf(-d2,0,1) - _underlyingPrice * cdf(-d1,0,1);
        _delta = cdf(d1,0,1)-1;
        break;
    default:
        break;
    }
    
}
double BlackScholesModel::getPrice()
{
    return _price;
}
double BlackScholesModel::getDelta()
{
    return _delta;
}
std::string BlackScholesModel::toString()
{
    return  std::to_string(_price) +" its delta is : "+std::to_string(_delta)+" with the Black-Scholes Model.\n";
}

