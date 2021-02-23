#include "PricerCrr.h"


double PricerCrr::factorial(int number)
{
	double factoRes = 1;
	for (int i = 1;i <= number;i++) {
		factoRes *= i;
	}
	return factoRes;
}

PricerCrr::PricerCrr(Option* option, double underlyingPrice, double riskFreeRate, double upFactor, double downFactor)
{
	_optionToCompute = option;
	_underlyingPrice = underlyingPrice;
	_riskFreeRate = riskFreeRate;
	_upFactor = upFactor;
	_downFactor = downFactor;
    _typeFormula = "ERROR no execution of the pricer"; // By default no execution so no formula has been used yet.
	_price = NULL;
}
PricerCrr::PricerCrr(Option* option, double underlyingPrice,double riskFreeRate)
{
    _optionToCompute = option;
    _underlyingPrice = underlyingPrice;
    _riskFreeRate = riskFreeRate;
    _upFactor = NULL;
    _downFactor = NULL;
    _typeFormula = "ERROR no execution of the pricer"; // By default no execution so no formula has been used yet.
    _price = NULL;
}
PricerCrr::~PricerCrr()
{
}
void PricerCrr::pricingWithClosedFormFormula(int nbSteps)
{
    _typeFormula = "Closed Form Formula";
    double riskNeutralProbability = (_riskFreeRate - _downFactor) / (_upFactor - _downFactor);
    std::vector<double> payOffVector;
    payOffVector.resize(nbSteps + 1);

    //Compute payOff at maturity
    for (int i = 0;i <= nbSteps;i++) {
        payOffVector[i] = _optionToCompute->payOff(_underlyingPrice * pow(1 + _upFactor, i) * pow(1 + _downFactor, nbSteps - i));
    }

    double price = 0;
    //Compute price based on payOff at maturity
    for (int i = 0;i <= nbSteps;i++) {
        price += (1 / (factorial(i) * factorial(nbSteps - i))) * pow(riskNeutralProbability, i) * pow((1 - riskNeutralProbability), nbSteps - i) * payOffVector[i];
    }

    //Set the price with the closed form formula
    _price = (factorial(nbSteps) / pow((1 + _riskFreeRate), nbSteps) * price);
    
}
void PricerCrr::pricingWithClosedFormFormulaWithBlackScholesAsLimit(int nbSteps,double volatility)
{
    //Set parameters to BlackScholes limit parameters
    double deltaT = _optionToCompute->getMaturity() / nbSteps;
    _upFactor = exp((_riskFreeRate + ((volatility * volatility) / 2)) * deltaT + (volatility * sqrt(deltaT))) - 1;
    _downFactor = exp((_riskFreeRate + ((volatility * volatility) / 2)) * deltaT - (volatility * sqrt(deltaT))) - 1;
    _riskFreeRate = exp(_riskFreeRate * deltaT) - 1;


    _typeFormula = "Closed Form Formula with black scholes limits";
    double riskNeutralProbability = (_riskFreeRate - _downFactor) / (_upFactor - _downFactor);
    std::vector<double> payOffVector;
    payOffVector.resize(nbSteps + 1);

    //Compute payOff at maturity
    for (int i = 0;i <= nbSteps;i++) {
        payOffVector[i] = _optionToCompute->payOff(_underlyingPrice * pow(1 + _upFactor, i) * pow(1 + _downFactor, nbSteps - i));
    }

    double price = 0;
    //Compute price based on payOff at maturity
    for (int i = 0;i <= nbSteps;i++) {
        price += (1 / (factorial(i) * factorial(nbSteps - i))) * pow(riskNeutralProbability, i) * pow((1 - riskNeutralProbability), nbSteps - i) * payOffVector[i];
    }

    //Set the price with the closed form formula
    _price = (factorial(nbSteps) / pow((1 + _riskFreeRate), nbSteps) * price);
}
void PricerCrr::pricingWithCrrModel(int nbSteps,bool us)
{
    _typeFormula = "CRR Model";
    double Hi1;
    double Hi;

    double riskNeutralProbability = (_riskFreeRate - _downFactor) / (_upFactor - _downFactor);

    //Vector resizing : would contain nbSteps vectors
    _underlyingPricesVector.setN(nbSteps);
    _payOffVector.setN(nbSteps);
    _optionPricesVector.setN(nbSteps);

    //Fill in the price tree
    for (int n = 0;n <= nbSteps;n++) {
        for (int i = 0;i <= n ;i++) {
            //Calculation of the price of the underlay according to its position in the tree
            double price = _underlyingPrice * pow(1 + _upFactor, i) * pow(1 + _downFactor, n - i);
            _underlyingPricesVector.setNode(n, i, price);
        }
    }

    //The last column of the tree corresponding to the payOff of the option at maturity is filled in.
    for (int i = nbSteps;i >= 0;i--) {  
        //double val = _optionToCompute->payOff(_underlyingPrice * pow(1 + _upFactor, i) * pow(1 + _downFactor, nbSteps - i));
        double val = _optionToCompute->payOff(_underlyingPricesVector.getNode(nbSteps, i));
        _payOffVector.setNode(nbSteps, i, val);
        _optionPricesVector.setNode(nbSteps, i, val);
    }

    //Compute prices for each node

    //If the option is with a pricing type US
    if ( us ) {
        for (int n = nbSteps - 1;n >= 0;n--) {
            for (int i = 0;i <= n;i++) {

                Hi1 = _optionPricesVector.getNode(n + 1, i + 1);
                Hi = _optionPricesVector.getNode(n + 1, i);

                //Calculates the payOff of this node
                double poff = _optionToCompute->payOff(_underlyingPricesVector.getNode(n, i));
                //Calculate the value of this node
                double val = std::max(((riskNeutralProbability * Hi1) + ((1 - riskNeutralProbability) * Hi)) / (1 + _riskFreeRate), poff);

                _optionPricesVector.setNode(n, i, val);
                _payOffVector.setNode(n, i, poff);
            }
        }
    }

    //If the price isn't calculate like the US one
    else {
        for (int n = nbSteps - 1;n >= 0;n--) {
            for (int i = 0;i <= n;i++) {

                Hi1 = _optionPricesVector.getNode(n + 1, i + 1);
                Hi = _optionPricesVector.getNode(n + 1, i);

                double val = ((riskNeutralProbability * Hi1) + ((1 - riskNeutralProbability) * Hi)) / (1 + _riskFreeRate);

                _optionPricesVector.setNode(n, i, val);
            }
        }
       
    }

    //Set the price
    _price = _optionPricesVector.getNode(0, 0);

}
void PricerCrr::pricingWithCrrModelWithBlackScholesAsLimit(int nbSteps, double volatility, bool us) {
    _typeFormula = "CRR Model with Black-Scholes as limits";

    //Set parameters to BlackScholes limit parameters
    double deltaT = _optionToCompute->getMaturity() / nbSteps;
    _upFactor = exp((_riskFreeRate + ((volatility * volatility) / 2)) * deltaT + (volatility * sqrt(deltaT))) - 1;
    _downFactor = exp((_riskFreeRate + ((volatility * volatility) / 2)) * deltaT - (volatility * sqrt(deltaT))) - 1;
    _riskFreeRate = exp(_riskFreeRate * deltaT) - 1;
    double Hi1;
    double Hi;

    double riskNeutralProbability = (_riskFreeRate - _downFactor) / (_upFactor - _downFactor);

    //Vector resizing : would contain nbSteps vectors
    _underlyingPricesVector.setN(nbSteps);
    _payOffVector.setN(nbSteps);
    _optionPricesVector.setN(nbSteps);

    //Fill in the price tree
    for (int n = 0;n <= nbSteps;n++) {
        for (int i = 0;i <= n;i++) {
            double price = _underlyingPrice * pow(1 + _upFactor, i) * pow(1 + _downFactor, n - i);
            _underlyingPricesVector.setNode(n, i, price);
        }
    }

    //The last column of the tree corresponding to the payOff of the option at maturity is filled in.
    for (int i = nbSteps;i >= 0;i--) {

        //double val = _optionToCompute->payOff(_underlyingPrice * pow(1 + _upFactor, i) * pow(1 + _downFactor, nbSteps - i));
        double val = _optionToCompute->payOff(_underlyingPricesVector.getNode(nbSteps, i));
        _payOffVector.setNode(nbSteps, i, val);
        _optionPricesVector.setNode(nbSteps, i, val);
    }

    //Compute prices for each node
    //If the option is with a pricing type US
    if (us) {
        for (int n = nbSteps - 1;n >= 0;n--) {
            for (int i = 0;i <= n;i++) {

                Hi1 = _optionPricesVector.getNode(n + 1, i + 1);
                Hi = _optionPricesVector.getNode(n + 1, i);

                double poff = _optionToCompute->payOff(_underlyingPricesVector.getNode(n, i));
                double val = std::max(((riskNeutralProbability * Hi1) + ((1 - riskNeutralProbability) * Hi)) / (1 + _riskFreeRate), poff);

                _optionPricesVector.setNode(n, i, val);
                _payOffVector.setNode(n, i, poff);
            }
        }
    }
    //If the price isn't calculate like the US one
    else {
        for (int n = nbSteps - 1;n >= 0;n--) {
            for (int i = 0;i <= n;i++) {

                Hi1 = _optionPricesVector.getNode(n + 1, i + 1);
                Hi = _optionPricesVector.getNode(n + 1, i);

                double val = ((riskNeutralProbability * Hi1) + ((1 - riskNeutralProbability) * Hi)) / (1 + _riskFreeRate);
                _optionPricesVector.setNode(n, i, val);
            }
        }
        
    }

    _price = _optionPricesVector.getNode(0, 0);
}
BinLattice<double> PricerCrr::getTreePrices()
{
    return _underlyingPricesVector;
}
BinLattice<double> PricerCrr::getTreePayOff()
{
    return _payOffVector;
}
std::string PricerCrr::toString()
{
    return std::to_string(_price) + " with the "+_typeFormula+".\n";
}

