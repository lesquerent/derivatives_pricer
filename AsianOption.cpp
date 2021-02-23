#include "AsianOption.h"
#include <iostream>
#include<iostream>



AsianOption::AsianOption(TypeOption optionType, double strikePrice, double maturity)
	: Option(optionType, strikePrice, maturity) {}
AsianOption::~AsianOption()
{
}

double AsianOption::meanPayOff(std::vector<std::vector<double>> pricesVector)
{
	double meanPayOff=0;
	double sum;

	int nbSequences = pricesVector.size();
	int nbPath = pricesVector[0].size()-1;

	for (int n = 0; n <= nbSequences - 1;n++) {

		sum = 0;

		for (int i = 0; i <= nbPath ;i++) {
			sum += pricesVector[n][i];
		}

		meanPayOff += payOff(sum / nbPath);
	}
	
	return (meanPayOff/nbSequences);
}
double AsianOption::payOff(double meanOfPrices)
{
	double resPayOff=0;
	switch (_type)
	{
	case TypeOption::call:
		resPayOff = std::max(meanOfPrices - _strikePrice, 0.);
		break;
	case TypeOption::put:
		resPayOff = std::max(_strikePrice - meanOfPrices, 0.);
		break;
	default:
		break;
	}
	return resPayOff;
}
double AsianOption::meanPrice(std::vector<double> pricesVector)
{
	double meanPrices = 0;
	double sum;

	double nbPath = pricesVector.size();

	sum = 0;
	for (int i = 1; i < nbPath;i++) {
		sum += pricesVector[i];
	}
	meanPrices += sum / (nbPath-1.);
	

	return (meanPrices);
}
std::tuple<double, double> AsianOption::meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector)
{
	int nbSequences = pricesVector.size();
	int nbPath = pricesVector[0].size() -1;

	double meanPayOff = 0.;
	double meanSquaredPayOff = 0.;

	for (int i = 0;i <= nbSequences - 1;i++) {
		//Calcul the payoff
		double actualPayOff = payOff(meanPrice(pricesVector[i]));

		meanPayOff += actualPayOff;

		meanSquaredPayOff += actualPayOff * actualPayOff;
	}

	return std::make_tuple(meanPayOff / nbSequences, meanSquaredPayOff / nbSequences);
}


