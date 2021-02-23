#pragma once
#include <iostream>
#include <random>

class SingletonMersenTwister
{
public:
	SingletonMersenTwister(const SingletonMersenTwister&) = delete; //empeche de pouvoir copier le singleton et donc d'en avoir deux

	static SingletonMersenTwister& getInstance();
	static std::mt19937 gen;

private:
	SingletonMersenTwister();

};

