#include "libm/trig.h"

double sin(double x) {
  double res = 0.0;
  double x_pow = x;        // Start with x (x^1 = x)
  double factorial = 1.0;  // 0! = 1

  for (int i = 0; i < ACCURACY_SIN; i++) {
    int sign = (i % 2 == 0) ? 1 : -1;
    res += sign * x_pow / factorial;

    // Update x_pow and factorial for the next term
    x_pow *= x * x;   // x_pow = x^(2i+3)
    factorial *= (2 * i + 2) * (2 * i + 3); // (2i+3)!
  }

  return res;
}

double cos(double x){
  return sin(x + MODIFIER);
}