#pragma once

#include "Option.h"
class AsianOption : public Option
{
public:
	AsianOption(TypeOption optionType, double strikePrice, double maturity);
	~AsianOption();

	/// <summary>
	/// Returns the average price over a period of time.
	/// </summary>
	/// <param name="pricesVector">Vector containing the evolution of the price on a sequence</param>
	/// <returns>Average prices over the period</returns>
	double meanPrice(std::vector<double> pricesVector);

	/// <summary>
	/// Returns the payOff of the option
	/// </summary>
	/// <param name="price">Option value at maturity</param>
	/// <returns>PayOff at maturity</returns>
	double payOff(double meanOfPrices);
	/// <summary>
	/// Returns the average payOff expected at maturity
	/// </summary>
	/// <param name="pricesVector">Vector containing the sequences of all awards to maturity</param>
	/// <returns>the average payOff expected at maturity</returns>
	double meanPayOff(std::vector<std::vector<double>> pricesVector);
	/// <summary>
	/// Returns the average payOff expected at maturity and the average squared payoff at maturity
	/// </summary>
	/// <param name="pricesVector">Vector containing the sequences of all awards to maturity</param>
	/// <returns>tuple of double, (mean of payoff at maturity, mean of payoff squared at maturity)</returns>
	std::tuple<double, double> meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector);
};
