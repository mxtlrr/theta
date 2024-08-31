#include "cmd-parse.h"

function_t functions[256];
void register_function(uint8_t function, char* common_name, function_t f){
	printf("[ OK ] Adding %s to math functions vector as ID=%d.\n",
						common_name, function);
	functions[function] = f;
}

float handle_function(uint8_t vector, float parameter){
	if(functions[vector] != 0){
		function_t vc = functions[vector];
		float val = vc(parameter);
		return val;
	}
	return 0.0f;
}

void parse_instruction(char* fmt){
	// Get coefficient
	bool valid_coefficient = false;
	if(fmt[0] >= 0x61 && fmt[0] <= 0x7a) valid_coefficient = false;
	else valid_coefficient = true;


	char coefficient_str[20] = {0};
	char operations[20] = {0};
	int op_ct = 0; int op_loc = 0;

	if(valid_coefficient){
		for(int i = 0; i < 20; i++){
			if(fmt[i] == '+' || fmt[i] == '-' || fmt[i] == '*' || fmt[i] == '/'){
					operations[op_ct] = fmt[i];
					op_loc = i;
					op_ct++;
					break;
			}
			coefficient_str[i] = fmt[i];
		}
	}

	bool isDecimal = containsChar(coefficient_str, '.');

	if(isDecimal == false && valid_coefficient == true){
		// Parse the second instruction
		if(fmt[op_loc+1] < 0x10){
			printf("fmt[%d] (%c) is a digit!\n", op_loc+1, fmt[op_loc+1]);
			// Do something, it's a digit.
		} else {
			// Fucntion/string

			// Invalid function!
			if(!(fmt[op_loc+1] >= 61 && fmt[op_loc+1] <= 0x7a)){
				printf("fmt[%d] (%c) is not an ascii char\n", op_loc+1,
							fmt[op_loc+1]);
				return;
			}
			if(fmt[op_loc+4] != '('){
				printf("fmt[%d] (%c) is not a parenthesis\n", op_loc+4,
						fmt[op_loc+4]);
			}
			switch(fmt[op_loc+1]){
				case 's': // Sine function
					char parameter[20];
					int counter = 0;
					for(int i = (op_loc+5); fmt[i] != ')'; i++) {
						parameter[counter] = fmt[i];
						counter++;
					}

					float parameter_ = stof(parameter);
					float res = handle_function(0, parameter_);

					printf("%f\n", (float)(stoi(coefficient_str)+res));
					break;
			}
		}
	}

	if(isDecimal == false && valid_coefficient == false){
		if(fmt[3] != '('){
			printf("fmt[%d] (%c) is not parenthesis\n", 3, fmt[3]);
			return;
		}
		switch(fmt[0]){
			case 's':
				char parameter[20];
				int counter = 0;
				for(int i = 4; fmt[i] != ')'; i++) {
					parameter[counter] = fmt[i];
					counter++;
				}

				float parameter_ = stof(parameter);
				float res = handle_function(0, parameter_);

				printf("%f\n", res);
				break;
		}
	}
}

