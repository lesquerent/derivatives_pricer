#pragma once
#include "Option.h"
#include "EuropeanOption.h"
#include"EuropeanDigitalOption.h"
#include "AsianOption.h"
#include"AmericanOption.h"
#include <iostream>
#include <vector>

class CrrModel : public AmericanOption, AsianOption,EuropeanOption,EuropeanDigitalOption
{

private:
	int _nbSteps; //N
	double _upFactor; //U
	double _downFactor; //D
	double _riskFreeRate; //R
	double _riskNeutralProbability; //q

	std::vector<std::vector<double>> _tree; //tree with prices
	

public:
	CrrModel(TypeOption optionType, double strikePrice, double expiryDate, double underlyingPrice, double interestRate, double volatility, int nbSteps, double upFactor, double downFactor,
		double riskFreeRate);
	static double factorial(double number);
	void compute();
	void computeClosedFormFormula();

	std::vector<std::vector<double>> getTree();
	double getPrice();
};

