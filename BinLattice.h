#pragma once
#include <vector>
#include <iostream>
#include<sstream>

template<typename TypeVector> class BinLattice
{
private:
	int _N=0;
	std::vector<std::vector<TypeVector>> _lattice;

public:

	/// <summary>
	/// Initializes the binomial tree
	/// </summary>
	/// <param name="n"></param>
	void setN(int n);
	/// <summary>
	/// Modifies the (n,i) node with the value val
	/// </summary>
	/// <param name="n"></param>
	/// <param name="i"></param>
	/// <param name="val"></param>
	void setNode(int n, int i,TypeVector val);

	/// <summary>
	/// Displays the tree in the simplest step-by-step way
	/// </summary>
	void display();
	/// <summary>
	/// Displays the tree in the shape of a pyramid without the branches.
	/// </summary>
	void display2();
	/// <summary>
	/// Displays the tree in the shape of a pyramid with branches
	/// </summary>
	void display3();

	/// <summary>
	/// Static function to return the version rounded to the hundredth of the tree
	/// </summary>
	/// <param name="payOff"></param>
	/// <returns></returns>
	static BinLattice<double> decimalPayOffTree(BinLattice<double> payOff);
	/// <summary>
	/// Static function to return the decision tree version according to the payOff value
	/// </summary>
	/// <param name="payOff"></param>
	/// <returns></returns>
	static BinLattice<bool> boolPayOffTree(BinLattice<double> payOff);

	int getN();
	TypeVector getNode(int n, int i);

};

template<typename TypeVector>
inline void BinLattice<TypeVector>::setN(int n)
{
	_N = n;
	//Redimensionnement du vecteur : contiendrais _N vecteurs
	_lattice.resize(_N + 1);

	//Redimensionnement des vecteur correspondant au nb-ieme step (ex: _lattice[0].size = 1, _lattice[1].size = 2, _t_latticeree[4].size = 5
	for (int i = 0;i <= _N;i++) {
		_lattice[i].resize(i + 1);
	}
}

template<typename TypeVector>
inline void BinLattice<TypeVector>::setNode(int n, int i,TypeVector val)
{
	_lattice[n][i] = val;
}

template<typename TypeVector>
inline TypeVector BinLattice<TypeVector>::getNode(int n, int i)
{
	return _lattice[n][i];
}

template<typename TypeVector>
inline void BinLattice<TypeVector>::display()
{
	for (int n = 0;n <= _N;n++) {
		for (int i = 0;i <= n;i++) {
			std::cout << _lattice[n][i] << " ";
		}
		std::cout << std::endl;
	}
		
}

template<typename TypeVector>
inline void BinLattice<TypeVector>::display2()
{
	for (int n = 0;n <= _N;n++) {

		for (int k = 0; k <= _N - n; k++) {
			std::cout << "  ";
		}

		for (int i = 0;i <= n;i++) {
			std::cout << _lattice[n][i] << "   ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	
	
}

template<typename TypeVector>
inline void BinLattice<TypeVector>::display3() {
	for (int i = 0; i <= 2 * _N; i++)
	{
		for (int k = 0; k <= (2 * _N - i); k++) { std::cout << " "; }
		if (i % 2 == 0)
		{
			for (int j = 0; j <= i / 2; j++)
			{
				std::cout << (_lattice[i / 2][j]);

				if (i > 0) { std::cout << "   "; }
			}
		}

		else
		{
			for (int j = 0; j <= i; j++)
			{
				if (j % 2 == 0) { std::cout << "/ "; }
				else { std::cout << "\\ "; }

			}

		}
		std::cout << "\n";
	}
}


template<typename TypeVector>
inline int BinLattice<TypeVector>::getN()
{
	return _N;
}

template<typename TypeVector>
inline BinLattice<double> BinLattice<TypeVector>::decimalPayOffTree(BinLattice<double> payOff)
{
	BinLattice<double> decimalPayOff;
	int nbSteps = payOff.getN();
	decimalPayOff.setN(nbSteps);
	for (int n = nbSteps ;n >= 0;n--) {
		for (int i = 0;i <= n;i++) {
			double node = payOff.getNode(n, i);
			double nb = int(node * 100.) / 100.;
			decimalPayOff.setNode(n, i, (1. / 100.) * floor(node * 100.));
		}

	}

	return decimalPayOff;

}

template<typename TypeVector>
inline BinLattice<bool> BinLattice<TypeVector>::boolPayOffTree(BinLattice<double> payOff)
{
	BinLattice<bool> boolPayOff;
	int nbSteps = payOff.getN();
	boolPayOff.setN(nbSteps);
	bool buy;
	for (int n = nbSteps;n >= 0;n--) {
		for (int i = 0;i <= n;i++) {
			double node = payOff.getNode(n, i);
			if (node > 0) {
				buy = true;
			}
			else {
				buy = false;
			}
			boolPayOff.setNode(n, i, buy);
		}
	}

	return boolPayOff;
}


