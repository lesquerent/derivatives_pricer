#pragma once
#include "Option.h"
#include "EuropeanOption.h"
#include"EuropeanDigitalOption.h"
#include "AsianOption.h"
#include"AmericanOption.h"


class BlackScholesModel 
{

private:
	#pragma region Attributs
	Option* _optionToCompute; //Pointer to the option to pricer

	double _underlyingPrice;//underlying price
	double _riskFreeRate; //interest rate
	double _volatility; //volatility of the underlying

	double _price; //prix
	double _delta; //Delta for this option.
	#pragma endregion

	/// <summary>
	/// Calculate the Gauss error function of x
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	double erf(double x);
	/// <summary>
	/// Calculate the cumulative distribution function (CDF) of a gaussin law of mean mu and variance sigma
	/// </summary>
	/// <param name="x"></param>
	/// <param name="mu"></param>
	/// <param name="sigma"></param>
	/// <returns></returns>
	double cdf(double x, double mu, double sigma);
public:
	BlackScholesModel(Option* optionToCompute, double underlyingPrice, double riskFreeRate, double volatility);
	~BlackScholesModel();
	/// <summary>
	/// Calculate the price and delta of an option
	/// </summary>
	void pricingWithBlackSholesModel();
	double getPrice();
	double getDelta();
	/// <summary>
	///Return a string (sentence) with the price and the delta of the option chosen
	/// </summary>
	/// <returns></returns>
	std::string toString();
};



