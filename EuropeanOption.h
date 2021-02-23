#pragma once
#include <iostream>
#include "Option.h"
class EuropeanOption : public Option
{
public:
	EuropeanOption(TypeOption optionType, double strikePrice, double expiryDate);
	~EuropeanOption();
	/// <summary>
	/// Virtual function, return the payOff of the option
	/// </summary>
	/// <param name="price">Option value at maturity</param>
	/// <returns>PayOff at maturity</returns>
	double payOff(double price);
	/// <summary>
	/// Virtual function, returns the average payOff expected at maturity
	/// </summary>
	/// <param name="pricesVector">: Vector containing the sequences of all awards to maturity</param>
	/// <returns>: the average payOff expected at maturity</returns>
	double meanPayOff(std::vector<std::vector<double>> pricesVector);
	/// <summary>
	/// Returns the average payOff expected at maturity and the average squared payoff at maturity
	/// </summary>
	/// <param name="pricesVector">: Vector containing the sequences of all awards to maturity</param>
	/// <returns>: tuple of double, (mean of payoff at maturity, mean of payoff squared at maturity)</returns>
	std::tuple<double,double> meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector);

};

