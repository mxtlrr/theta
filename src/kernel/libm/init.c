#include "libm/init.h"

void setup_functions(void){
	register_function(SIN_FUNCTION, "sin(x)", sin);
}
