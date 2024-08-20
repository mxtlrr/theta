#pragma once

#include "libm/arith.h"
#include "libm/constants.h"

#define ACCURACY_SIN 300 // How many terms of the taylor series are we doing?
double sin(double x);