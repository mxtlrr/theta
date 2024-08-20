#pragma once

#include "libm/arith.h"
#include "libm/constants.h"

#define ACCURACY_SIN 300 // How many terms of the taylor series are we doing?
double sin(double x);


#define MODIFIER (PI/2) // ~1.57
double cos(double x);
double tan(double x);