#include "EuropeanDigitalOption.h"


EuropeanDigitalOption::EuropeanDigitalOption(TypeOption optionType, double strikePrice, double expiryDate)
	: Option(optionType, strikePrice, expiryDate) {}

EuropeanDigitalOption::~EuropeanDigitalOption()
{
}
double EuropeanDigitalOption::payOff(double price)
{
    double payOff = NULL;
    switch (_type)
    {
    case TypeOption::call:
        if (price >= _strikePrice) { payOff = 1; }
        break;
    case TypeOption::put:
        if (price <= _strikePrice) { payOff = 1; }
        break;
    default:
        break;
    }

    return payOff;
}
double EuropeanDigitalOption::meanPayOff(std::vector<std::vector<double>> pricesVector)
{
    int nbSequences = pricesVector.size();
    int nbPath = pricesVector[0].size()-1;

    double meanPayOff = 0.;
    for (int i = 0;i <= nbSequences - 1;i++) {
        meanPayOff += payOff(pricesVector[i][nbPath]);
    }
    return meanPayOff / nbSequences;
}
std::tuple<double, double> EuropeanDigitalOption::meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector)
{
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
