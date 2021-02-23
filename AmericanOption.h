#pragma once

#include "Option.h"
#include "BinLattice.h"

class AmericanOption : public Option
{
public:
	AmericanOption(TypeOption optionType, double strikePrice, double maturity);
	~AmericanOption();

	/// <summary>
	/// Returns the payOff of the option
	/// </summary>
	/// <param name="price">Option value at maturity</param>
	/// <returns>PayOff at maturity</returns>
	double payOff(double price);
	/// <summary>
	/// Returns the average payOff expected at maturity
	/// </summary>
	/// <param name="pricesVector">Vector containing the sequences of all awards to maturity</param>
	/// <returns>the average payOff expected at maturity</returns>
	double meanPayOff(std::vector<std::vector<double>> pricesVector);
	/// <summary>
	/// Override from the virtual mother class but not use in American option, return a tuple of NULL
	/// </summary>
	/// <param name="pricesVector"></param>
	/// <returns></returns>
	std::tuple<double, double> meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector);


	BinLattice<bool> boolPayOff(BinLattice<double> payOff);
};
