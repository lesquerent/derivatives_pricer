#include "SingletonMersenTwister.h"

std::random_device rd;
std::mt19937 SingletonMersenTwister::gen(rd());

SingletonMersenTwister::SingletonMersenTwister()
{
	
	std::cout << "\n-------------------------------------------\n     Mersene-Twister generator created\n-------------------------------------------\n";
}

SingletonMersenTwister& SingletonMersenTwister::getInstance()
{
	static SingletonMersenTwister mersen_instance;
	return mersen_instance;
}