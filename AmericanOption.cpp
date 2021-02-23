#include "AmericanOption.h"


AmericanOption::AmericanOption(TypeOption optionType, double strikePrice, double maturity): Option(optionType, strikePrice, maturity) {}
AmericanOption::~AmericanOption()
{
}

double AmericanOption::payOff(double price)
{
   
    double payOff = NULL;
    switch (_type)
    {
    case TypeOption::call:
        payOff = std::max(price - _strikePrice, 0.);
        break;
    case TypeOption::put:
        payOff = std::max(_strikePrice - price, 0.);
        break;
    default:
        break;
    }

    return payOff;
    
}
double AmericanOption::meanPayOff(std::vector<std::vector<double>> pricesVector)
{

    int nbSequences = pricesVector.size();
    int nbPath = pricesVector.size()-1;
    return 0.0;
}
std::tuple<double, double> AmericanOption::meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector)
{
    return std::make_tuple(NULL,NULL);
}



BinLattice<bool> AmericanOption::boolPayOff(BinLattice<double> payOff)
{
    return BinLattice<bool>();
}



