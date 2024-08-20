#pragma once

#include "libm/constants.h"


// exp(n) = e^n
float exp(int n);

// pow(a,b) = a^b
int pow(int a, int b);

// z! = z * z-1 * z-2 * ... * 1
int fact(int z);

// Approximates the square root of some number n
#define ACCURACY 25
float sqrt(int n);