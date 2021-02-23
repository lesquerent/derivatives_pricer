#include "CrrModel.h"

double CrrModel::factorial(double number)
{
	double factoRes = 1;
	for (int i = 1;i <= number;i++) {
		factoRes *= i;
		}

	return factoRes;
}

CrrModel::CrrModel(TypeOption optionType, double strikePrice, double expiryDate, double underlyingPrice, double interestRate, double volatility, int nbSteps, double upFactor, double downFactor,
	double riskFreeRate) : EuropeanOption(optionType, strikePrice, expiryDate, underlyingPrice, interestRate, volatility)
{
	_nbSteps = nbSteps;
	_upFactor = upFactor;
	_downFactor = downFactor;
	_riskFreeRate = riskFreeRate;
	_riskNeutralProbability = (_riskFreeRate - _downFactor) / (_upFactor - _downFactor);
}

void CrrModel::compute()
{
	double Hi1;
	double Hi;
	//Redimensionnement du vecteur : contiendrais _nbSteps vecteurs
	_tree.resize(_nbSteps + 1);

	//Redimensionnement des vecteur correspondant au nb-ieme step (ex: _tree[0].size = 1, _tree[1].size = 2, _tree[4].size = 5
	for (int i = 0;i <= _nbSteps;i++) {
		_tree[i].resize(i+1);
	}


	//On remplit la dernière colonne de l'arbre correspondant au payOff de l'option à maturité
	for (int i = _nbSteps;i >= 0;i--) {
		_tree[_nbSteps][i]=this->payOff(_s*pow(1+_upFactor,i)*pow(1+_downFactor,_nbSteps-i)); 
	}

	//Compute prices for each node
	for (int i = _nbSteps-1 ;i >= 0;i--) {
		for (int j = 0;j <= i;j++){
			Hi1 = this->_tree[i + 1][j + 1];
			Hi = this->_tree[i + 1][j];

			_tree[i][j] = ((_riskNeutralProbability * Hi1) + ((1 - _riskNeutralProbability) * Hi)) / (1 + _riskFreeRate);
		}
	}

	_price = _tree[0][0];
}

void CrrModel::computeClosedFormFormula()
{
	std::vector<double> tree;
	tree.resize(_nbSteps + 1);

	//Compute les payOff à maturité
	for (int i = 0;i <= _nbSteps;i++) {
		tree[i] = this->payOff(_s * pow(1 + _upFactor, i) * pow(1 + _downFactor, _nbSteps - i));
	}

	double price=0;
	//Compute le prix en fonction des payOff à maturité
	for (int i = 0;i <= _nbSteps;i++) {
		price += (1 / (factorial(i) * factorial(_nbSteps - i))) * pow(_riskNeutralProbability, i) * pow((1 - _riskNeutralProbability), _nbSteps - i) * tree[i];
	}

	_price = factorial(_nbSteps) / pow((1 + _riskFreeRate), _nbSteps) * price;
}

std::vector<std::vector<double>> CrrModel::getTree()
{
	return _tree;
}

double CrrModel::getPrice()
{
	return _price;
}
