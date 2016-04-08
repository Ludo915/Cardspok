#pragma once
#include <iosfwd>
#include <cassert>
#include <cmath>
#ifndef RANDOM_H
#define RANDOM_H
class randomInteger {
public:
	unsigned int operator () (unsigned int);
} randomizer;

unsigned int randomInteger::operator () (unsigned int max)
{
	// rand return random integer
	// convert to unsigned to make positive
	// take remainder to put in range
	unsigned int rval = rand();
	return rval % max;
}

#endif	