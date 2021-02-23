#pragma once
#include <iostream>
#include <vector>
#include<tuple>


/// <summary>
/// Enum for the type of option to be priced, Call ou Put 
/// </summary>
enum class TypeOption {call, put};

class Option
{

protected:
	#pragma region Attributs
	TypeOption _type; //Type of option, call or put
	double _strikePrice; //strike price
	double _maturity;// expirity date	
	#pragma endregion

public:
	#pragma region Constructeur/Destructeur
	Option(TypeOption optionType, double strikePrice, double maturity);
	~Option();
	#pragma endregion
	#pragma region Getteur
	double getMaturity();
	TypeOption getType();
	double getStrikePrice();
	#pragma endregion

	/// <summary>
	/// Virtual function, return the payOff of the option
	/// </summary>
	/// <param name="price">Option value at maturity</param>
	/// <returns>PayOff at maturity</returns>
	virtual double payOff(double price) = 0;
	/// <summary>
	/// Virtual function, returns the average payOff expected at maturity
	/// </summary>
	/// <param name="pricesVector">Vector containing the sequences of all awards to maturity</param>
	/// <returns>the average payOff expected at maturity</returns>
	virtual double meanPayOff(std::vector<std::vector<double>> pricesVector) = 0;
	/// <summary>
	/// Virtual function, returns the average payOff expected at maturity and the average squared payoff at maturity
	/// </summary>
	/// <param name="pricesVector">Vector containing the sequences of all awards to maturity</param>
	/// <returns>tuple of double, (mean of payoff at maturity, mean of payoff squared at maturity)</returns>
	virtual std::tuple<double, double> meanMeanSquaredPayOff(std::vector<std::vector<double>> pricesVector)=0;

};

