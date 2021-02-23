#include "EuropeanOption.h"
#include <iostream>
#include <tuple>

EuropeanOption::EuropeanOption(TypeOption optionType, double strikePrice, double expiryDate)
	: Option(optionType, strikePrice, expiryDate){}
EuropeanOption::~EuropeanOption()
{
}

double EuropeanOption::payOff(double price)
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
std::tuple<double, double> EuropeanOption::meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector) {

    int nbSequences = pricesVector.size();
    int nbPath = pricesVector[0].size() - 1;

    double meanPayOff = 0.;
    double meanSquaredPayOff = 0.;
    for (int i = 0;i <= nbSequences - 1;i++) {
        double actualPayOff = payOff(pricesVector[i][nbPath]);
        meanPayOff += actualPayOff;
        meanSquaredPayOff += actualPayOff * actualPayOff;
    }

    return std::make_tuple(meanPayOff / nbSequences, meanSquaredPayOff / nbSequences);
}
double EuropeanOption::meanPayOff(std::vector<std::vector<double>> pricesVector)
{
    int nbSequences = pricesVector.size();
    int nbPath = pricesVector[0].size()-1;

    double meanPayOff = 0.;
    for (int i = 0;i <= nbSequences - 1;i++) {
        meanPayOff += payOff(pricesVector[i][nbPath]);
    }
    return meanPayOff / nbSequences;
}
