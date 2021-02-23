#include <iostream>
#include"EuropeanDigitalOption.h"
#include"EuropeanOption.h"
#include"AmericanOption.h"
#include"AsianOption.h"
#include"SingletonMersenTwister.h"
#include"PricerCrr.h"
#include "PricerMonteCarlo.h"
#include"BlackScholesModel.h"
#include"BinLattice.h"

/// N.B.1 : All prices in this pricer are at no time rounded in the calculations or in the displays (except for the BinLattice tree display).
/// This is entirely voluntary in order to keep as much precision as possible, the rounding being done at the operator's discretion according to the number of options used in the contract.
/// 
/// N.B.2 : A demo version of the pricer and all these features is available and launches when the code is launched.

/// <summary>
/// Fonctin used for the demo of the console, testing all the pricing possibilities.
/// </summary>
static void TestAllPricerConsole() {
	
	// Option Attributs
	
	TypeOption call = TypeOption::call;
	TypeOption put = TypeOption::put;
	double strikePrice = 101.;
	double expiryDate = 10.;

	// Pricer Attributs
	double underlyingPrice = 100.0;
	double riskFreeRate = 0.01;
	double volatility = 0.10;

	//Monte Carlo Attributs
	int nbPath = 10;
	int nbSequences = 10000;

	//CRR Attributs
	int nbSteps = 10;
	double upFactor = 0.05;
	double downFactor = -0.04762;

#pragma region Definition of options
	//                      Definition of options 

	//Call
	EuropeanOption optionCallEu = EuropeanOption(call, strikePrice, expiryDate);
	EuropeanDigitalOption optionCallEuDigit = EuropeanDigitalOption(call, strikePrice, expiryDate);
	AmericanOption optionCallUs = AmericanOption(call, strikePrice, expiryDate);
	AsianOption optionCallAsian = AsianOption(call, strikePrice, expiryDate);

	//Put
	EuropeanOption optionPutEu = EuropeanOption(put, strikePrice, expiryDate);
	EuropeanDigitalOption optionPutEuDigit = EuropeanDigitalOption(put, strikePrice, expiryDate);
	AmericanOption optionPutUs = AmericanOption(put, strikePrice, expiryDate);
	AsianOption optionPutAsian = AsianOption(put, strikePrice, expiryDate);
#pragma endregion

#pragma region Definition of models
	//                      Définition Of Models

	// ###################   Simple Black scholes  ###################
	//Call
	BlackScholesModel optionEuCallPriceWithBS = BlackScholesModel(&optionCallEu, underlyingPrice, riskFreeRate, volatility);

	//Put
	BlackScholesModel optionEuPutPriceWithBS = BlackScholesModel(&optionPutEu, underlyingPrice, riskFreeRate, volatility);

	// ###################      Crr Model     ###################


	//Call
	PricerCrr optionEuCallPriceWithCrr = PricerCrr(&optionCallEu, underlyingPrice, riskFreeRate, upFactor, downFactor);
	PricerCrr optionCallDigitalEuPriceWithCrr = PricerCrr(&optionCallEuDigit, underlyingPrice, riskFreeRate, upFactor, downFactor);
	PricerCrr optionCallUsPriceWithCrr = PricerCrr(&optionCallUs, underlyingPrice, riskFreeRate, upFactor, downFactor);

	//Put
	PricerCrr optionEuPutPriceWithCrr = PricerCrr(&optionPutEu, underlyingPrice, riskFreeRate, upFactor, downFactor);
	PricerCrr optionPutDigitialEuPriceWithCrr = PricerCrr(&optionPutEuDigit, underlyingPrice, riskFreeRate, upFactor, downFactor);
	PricerCrr optionPutUsPriceWithCrr = PricerCrr(&optionPutUs, underlyingPrice, riskFreeRate, upFactor, downFactor);

	// ###################      Closed Form Formula     ###################

	//Call
	PricerCrr optionEuCallPriceWithClosedFormFormula = PricerCrr(&optionCallEu, underlyingPrice, riskFreeRate, upFactor, downFactor);
	PricerCrr optionCallDigitalEuPriceWithClosedFormFormula = PricerCrr(&optionCallEuDigit, underlyingPrice, riskFreeRate, upFactor, downFactor);

	//Put
	PricerCrr optionEuPutPriceWithClosedFormFormula = PricerCrr(&optionPutEu, underlyingPrice, riskFreeRate, upFactor, downFactor);
	PricerCrr optionPutDigitialEuPriceWithCrrClosedFormFormula = PricerCrr(&optionPutEuDigit, underlyingPrice, riskFreeRate, upFactor, downFactor);
	
	// ###################      Crr Model With BS limits    ###################
	//Call
	PricerCrr optionEuCallPriceWithCrrWithBlackScholesAsLimit = PricerCrr(&optionCallEu, underlyingPrice, riskFreeRate);
	PricerCrr optionCallDigitalEuPriceWithCrrWithBlackScholesAsLimit = PricerCrr(&optionCallEuDigit, underlyingPrice, riskFreeRate);
	PricerCrr optionCallUsPriceWithCrrWithBlackScholesAsLimit = PricerCrr(&optionCallUs, underlyingPrice, riskFreeRate);

	//Put
	PricerCrr optionEuPutPriceWithCrrWithBlackScholesAsLimit = PricerCrr(&optionPutEu, underlyingPrice, riskFreeRate);
	PricerCrr optionPutDigitialEuPriceWithCrrWithBlackScholesAsLimit = PricerCrr(&optionPutEuDigit, underlyingPrice, riskFreeRate);
	PricerCrr optionPutUsPriceWithCrrWithBlackScholesAsLimit = PricerCrr(&optionPutUs, underlyingPrice, riskFreeRate);

	// ###################      Closed Form Formula With BS Limits   ###################
	//Call
	PricerCrr optionEuCallPriceWithClosedFormFormulaWithBlackScholesAsLimit = PricerCrr(&optionCallEu, underlyingPrice, riskFreeRate);
	PricerCrr optionCallDigitalEuPriceWithClosedFormFormulaWithBlackScholesAsLimit = PricerCrr(&optionCallEuDigit, underlyingPrice, riskFreeRate);
	

	//Put
	PricerCrr optionEuPutPriceWithClosedFormFormulaWithBlackScholesAsLimit = PricerCrr(&optionPutEu, underlyingPrice, riskFreeRate);
	PricerCrr optionPutDigitialEuPriceWithClosedFormFormulaWithBlackScholesAsLimit = PricerCrr(&optionPutEuDigit, underlyingPrice, riskFreeRate);

	// ###################      Monte Carlo   ###################

	//Call
	PricerMonteCarlo optionEuCallPriceWithMonteCarloMethod = PricerMonteCarlo(&optionCallEu, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);
	PricerMonteCarlo optionCallDigitalEuPriceWithMonteCarloMethod = PricerMonteCarlo(&optionCallEuDigit, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);
	PricerMonteCarlo optionCallAsianPriceWithMonteCarloMethod = PricerMonteCarlo(&optionCallAsian, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);

	//Put
	PricerMonteCarlo optionEuPutPriceWithMonteCarloMethod = PricerMonteCarlo(&optionPutEu, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);
	PricerMonteCarlo optionPutDigitialEuPriceWithMonteCarloMethod = PricerMonteCarlo(&optionPutEuDigit, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);
	PricerMonteCarlo optionPutAsianPriceWithMonteCarloMethod = PricerMonteCarlo(&optionPutAsian, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);
#pragma endregion

#pragma region Execution of models
	//                      Execution of models
	//Call
	//BS
	optionEuCallPriceWithBS.pricingWithBlackSholesModel();
	//CRR
	optionEuCallPriceWithCrr.pricingWithCrrModel(nbSteps);
	optionCallDigitalEuPriceWithCrr.pricingWithCrrModel(nbSteps);
	optionCallUsPriceWithCrr.pricingWithCrrModel(nbSteps, true);
	//Closed Form Formula
	optionEuCallPriceWithClosedFormFormula.pricingWithClosedFormFormula(nbSteps);
	optionCallDigitalEuPriceWithClosedFormFormula.pricingWithClosedFormFormula(nbSteps);

	//CRR BS Limit
	optionEuCallPriceWithCrrWithBlackScholesAsLimit.pricingWithCrrModelWithBlackScholesAsLimit(1000, volatility);
	optionCallDigitalEuPriceWithCrrWithBlackScholesAsLimit.pricingWithCrrModelWithBlackScholesAsLimit(nbSteps, volatility);
	optionCallUsPriceWithCrrWithBlackScholesAsLimit.pricingWithCrrModelWithBlackScholesAsLimit(nbSteps, volatility, true);

	//Closed Form Formula BS limit
	optionEuCallPriceWithClosedFormFormulaWithBlackScholesAsLimit.pricingWithClosedFormFormulaWithBlackScholesAsLimit(nbSteps, volatility);
	optionCallDigitalEuPriceWithClosedFormFormulaWithBlackScholesAsLimit.pricingWithClosedFormFormulaWithBlackScholesAsLimit(nbSteps, volatility);
	
	//Monte Carlo
	optionEuCallPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();
	optionCallDigitalEuPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();
	optionCallAsianPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();


	//Put	
	//BS
	optionEuPutPriceWithBS.pricingWithBlackSholesModel();

	//CRR
	optionEuPutPriceWithCrr.pricingWithCrrModel(nbSteps);
	optionPutDigitialEuPriceWithCrr.pricingWithCrrModel(nbSteps);
	optionPutUsPriceWithCrr.pricingWithCrrModel(nbSteps, true);

	//Closed Form Formula
	optionEuPutPriceWithClosedFormFormula.pricingWithClosedFormFormula(nbSteps);
	optionPutDigitialEuPriceWithCrrClosedFormFormula.pricingWithClosedFormFormula(nbSteps);

	//CRR BS as limit
	optionEuPutPriceWithCrrWithBlackScholesAsLimit.pricingWithCrrModelWithBlackScholesAsLimit(nbSteps, volatility);
	optionPutDigitialEuPriceWithCrrWithBlackScholesAsLimit.pricingWithCrrModelWithBlackScholesAsLimit(nbSteps, volatility);
	optionPutUsPriceWithCrrWithBlackScholesAsLimit.pricingWithCrrModelWithBlackScholesAsLimit(nbSteps, volatility, true);

	//Closed Form Formula BS limit
	optionEuPutPriceWithClosedFormFormulaWithBlackScholesAsLimit.pricingWithClosedFormFormulaWithBlackScholesAsLimit(nbSteps, volatility);
	optionPutDigitialEuPriceWithClosedFormFormulaWithBlackScholesAsLimit.pricingWithClosedFormFormulaWithBlackScholesAsLimit(nbSteps, volatility);

	//Monte Carlo
	optionEuPutPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();
	optionPutDigitialEuPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();
	optionPutAsianPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();
#pragma endregion

#pragma region Pricing Display
	// Affichage of pricing
	
	std::cout << "\nStrike price : " << strikePrice;
	std::cout << "\nExpirity date : " << expiryDate;

	std::cout << "\n\nPricers attributs :";
	std::cout << "\nUnderlying price : " << underlyingPrice;
	std::cout << "\nRisk free rate : " << riskFreeRate;
	std::cout << "\nVolatility : " << volatility;

	std::cout << "\n\nMonte Carlo attributs :";
	std::cout << "\nNumber of price until maturity : " << nbPath;
	std::cout << "\nNumber of sequences of prices : " << nbSequences;

	std::cout << "\n\nCRR attributs : ";
	std::cout << "\nNumber of steps : " << nbSteps;
	std::cout << "\nUp factor : " << upFactor;
	std::cout << "\nDown factor : " << downFactor<<std::endl;

	std::cout << "\n##### European Call Option ##### " << std::endl;
	std::cout << optionEuCallPriceWithBS.toString();
	std::cout << optionEuCallPriceWithCrr.toString();
	std::cout << optionEuCallPriceWithClosedFormFormula.toString();
	std::cout << optionEuCallPriceWithCrrWithBlackScholesAsLimit.toString();
	std::cout << optionEuCallPriceWithClosedFormFormulaWithBlackScholesAsLimit.toString();
	std::cout << optionEuCallPriceWithMonteCarloMethod.toString(95);

	std::cout << "\n##### European Put Option ##### " << std::endl;
	std::cout << optionEuPutPriceWithBS.toString();
	std::cout << optionEuPutPriceWithCrr.toString();
	std::cout << optionEuPutPriceWithClosedFormFormula.toString();
	std::cout << optionEuPutPriceWithCrrWithBlackScholesAsLimit.toString();
	std::cout << optionEuPutPriceWithClosedFormFormulaWithBlackScholesAsLimit.toString();
	std::cout << optionEuPutPriceWithMonteCarloMethod.toString(95);

	std::cout << "\n##### European Digital Call Option ##### " << std::endl;
	std::cout << optionCallDigitalEuPriceWithCrr.toString();
	std::cout << optionCallDigitalEuPriceWithClosedFormFormula.toString();
	std::cout << optionCallDigitalEuPriceWithCrrWithBlackScholesAsLimit.toString();
	std::cout << optionCallDigitalEuPriceWithClosedFormFormulaWithBlackScholesAsLimit.toString();
	std::cout << optionCallDigitalEuPriceWithMonteCarloMethod.toString(95);

	std::cout << "\n##### European Digital Put Option ##### " << std::endl;
	std::cout << optionPutDigitialEuPriceWithCrr.toString();
	std::cout << optionPutDigitialEuPriceWithCrrClosedFormFormula.toString();
	std::cout << optionPutDigitialEuPriceWithCrrWithBlackScholesAsLimit.toString();
	std::cout << optionPutDigitialEuPriceWithClosedFormFormulaWithBlackScholesAsLimit.toString();
	std::cout << optionPutDigitialEuPriceWithMonteCarloMethod.toString(95);

	std::cout << "\n##### American Call Option ##### " << std::endl;
	std::cout << optionCallUsPriceWithCrr.toString();
	std::cout << optionCallUsPriceWithCrrWithBlackScholesAsLimit.toString();


	std::cout << "\n##### American Put Option ##### " << std::endl;
	std::cout << optionPutUsPriceWithCrr.toString();
	std::cout << optionPutUsPriceWithCrrWithBlackScholesAsLimit.toString();

	std::cout << "\n##### Asian Call Option ##### " << std::endl;
	std::cout << optionCallAsianPriceWithMonteCarloMethod.toString(95);


	std::cout << "\n##### Asian Put Option ##### " << std::endl;
	std::cout << optionPutAsianPriceWithMonteCarloMethod.toString(95);
#pragma endregion
}
/// <summary>
/// Fonctin used for the demo of the console, testing all the Monte Carlo refine possibility.
/// </summary>
static void TestDetailsMonteCarloPricerConsole() {

	// Option Attributs
	TypeOption call = TypeOption::call;
	double strikePrice = 101.;
	double expiryDate = 10;

	double underlyingPrice = 100.0;
	double riskFreeRate = 0.01;
	double volatility = 0.10;

	EuropeanOption optionCallEu = EuropeanOption(call, strikePrice, expiryDate);
	
	//Monte Carlo Attributs
	int nbPath = 1000;
	int nbSequences = 10;

	PricerMonteCarlo optionEuCallPriceWithMonteCarloMethod = PricerMonteCarlo(&optionCallEu, underlyingPrice, riskFreeRate, volatility, nbPath, nbSequences);
	optionEuCallPriceWithMonteCarloMethod.pricinWithMonteCarloMethod();
	
	
	
	std::cout<<"\n\nOptions attributs : ";
	std::cout << "\nStrike price : " << strikePrice;
	std::cout << "\nExpirity date : " << expiryDate;

	std::cout << "\n\nPricers attributs :";
	std::cout << "\nUnderlying price : " << underlyingPrice;
	std::cout << "\nRisk free rate : " << riskFreeRate;
	std::cout << "\nVolatility : " << volatility;

	std::cout << "\n\nMonte Carlo attributs :";
	std::cout << "\nNumber of price until maturity : " << nbPath;
	std::cout << "\nNumber of sequences of prices : " << nbSequences;

	std::cout << "\n\nPrice : " << optionEuCallPriceWithMonteCarloMethod.toString(95);

	for (int i = 1;i <= 30;i++) {
		//nbSequences = nbSequences * 10;
		optionEuCallPriceWithMonteCarloMethod.refines(1000);
		std::cout << "Price : " << optionEuCallPriceWithMonteCarloMethod.toString(95);
	}
	
}
/// <summary>
/// Fonctin used for the demo of the console, testing all the possibilities to display the binLattice class.
/// </summary>
static void TestBinLatticeInDetail() {
	// Option Attributs
	TypeOption call = TypeOption::call;
	TypeOption put = TypeOption::put;
	double strikePrice = 101;
	double expiryDate = 1.0;
	double underlyingPrice = 100.0;
	double interestRate = 0.05;
	double volatility = 0.30;

	AmericanOption optionCallUs = AmericanOption(call, strikePrice, expiryDate);

	//CRR Attributs

	int nbSteps = 10;
	double upFactor = 0.05;
	double downFactor = -0.04762;
	double riskFreeRate = 0.01;

	PricerCrr optionCallUsPriceWithCrr = PricerCrr(&optionCallUs, underlyingPrice, riskFreeRate, upFactor, downFactor);

	optionCallUsPriceWithCrr.pricingWithCrrModel(nbSteps, true);

	std::cout << "\n##### Lattice Display #####" << std::endl;
	std::cout<<"\nOptions attributs : ";
	std::cout << "\nStrike price : " << strikePrice;
	std::cout << "\nExpirity date : " << expiryDate;

	std::cout << "\n\nPricers attributs :";
	std::cout << "\nUnderlying price : " << underlyingPrice;
	std::cout << "\nRisk free rate : " << riskFreeRate;
	std::cout << "\nVolatility : " << volatility;

	std::cout << "\n\nCRR attributs : ";
	std::cout << "\nNumber of steps : " << nbSteps;
	std::cout << "\nUp factor : " << upFactor;
	std::cout << "\nDown factor : " << downFactor << std::endl;
	std::cout << "Different Lattice for American call Option : \n";

	//Create and display the price tree
	BinLattice<double> decimalPriceTree;
	decimalPriceTree = BinLattice<double>::decimalPayOffTree(optionCallUsPriceWithCrr.getTreePrices());
	std::cout << "\nTree composed of underlying prices : \n";
	decimalPriceTree.display();

	//Create and display the payOff tree
	BinLattice<double> decimalPayoffTree;
	decimalPayoffTree = BinLattice<double>::decimalPayOffTree(optionCallUsPriceWithCrr.getTreePayOff());
	std::cout << "\nTree composed of payOff : \n";
	decimalPayoffTree.display2();

	//Create and display the execution decision tree
	BinLattice<bool> boolPayoffTree;
	boolPayoffTree = BinLattice<bool>::boolPayOffTree(optionCallUsPriceWithCrr.getTreePayOff());
	std::cout << "\nTree representing whether or not the option can be executed (yes=1, no=0) : \n";
	boolPayoffTree.display3();
}

int main() {
	int choice=-1;
	std::string menu;
	menu = std::string("\n\n                          ####         Menu         ####\n")
		+std::string("1. Demonstration of all possible pricing methods for each option.\n")
		+ std::string("2. Demonstration of the display of a binomial tree using binlattice in the case of an american option.\n")
		+ std::string("3. Demonstration of the possibilities to improve a Monte Carlo estimated price.\n")
		+ std::string("0. Fermer la console.");

	while (choice != 0) {

		std::cout << menu;
		std::cout << "\n\nChoose the menu of your choice : ";
		std::cin >> choice;
		std::cout << std::endl << std::endl;

		switch (choice)
		{
		case 0:
			std::cout << "Press enter to close the window.\n";
			break;

		case 1:
			std::cout << "\n#INFO  : In this part of the demonstration you will see the price for all possible options with all possible methods with the following data :\n\nOptions attributs :";
			TestAllPricerConsole();
			break;

		case 3:
			std::cout << "\n#INFO In this part of the demonstration you will see the evolution of the estimation of a price for a European option using the monte carlo method and the refine(nbSequences) function." << std::endl;
			TestDetailsMonteCarloPricerConsole();
			break;

		case 2:
			TestBinLatticeInDetail();
			break;

		default:
			break;
		}
	}

}