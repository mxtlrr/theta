#include "libc/math.h"

int pow(int a, int b){
	int res = a;
	for(int i = 1; i != b; i++){
		res *= a;
	}
	return res;
}