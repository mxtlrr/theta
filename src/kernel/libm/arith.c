#include "libm/arith.h"

float exp(int n){
  float res = E;
  for(int i = 1; i < n; i++){
    res *= E;
  }
  return res;
}

int pow(int a, int b){
  int res = a;
  for(int i = 1; i < b; i++) res *= a;
  return res;
}

int fact(int z){
  int res = 1;
  for(int i = z; i != 1; i--){
    res *= i;
  }
  return res;
}

float sqrt(int n){
  float S   = n;
  float x_n = n;
  for(int i = 0; i < ACCURACY; i++){
    x_n = 0.5 * (x_n + S/x_n);
  }
  return x_n;
}