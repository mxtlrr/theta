#pragma once

#include "libm/arith.h"
#include "libm/constants.h"

#define ACCURACY_SIN 300 // How many terms of the taylor series are we doing?
double sin(double x);


// Approximately, cos(x) = sin(x + (0.5 * (5pi - 12))).
// aka, cos(x) = sin(x + 1.85398). Cursed, but works :^)
#define MODIFIER (0.5 * ((5*PI) - 12))
double cos(double x);