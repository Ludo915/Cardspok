#pragma once
#include <iosfwd>
#include <cassert>
#include <cmath>
#ifndef RANDOM_H
#define RANDOM_H
class RandomInteger
{
	RandomInteger(int Decksize);
	
	friend int RandomInteger(int Decksize) //variable aleatoire uniforme [0,1] methode random sequence
	{
		int V1 = float(1. + rand()) / float(1. + Decksize);
		return V1;
	}
};