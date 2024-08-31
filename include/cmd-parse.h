#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "video/stdio.h"

typedef double (*function_t)(double input);
extern function_t functions[256];

void register_function(uint8_t function, char* common_name, function_t f);
float handle_function(uint8_t vector, float parameter);

// Parse instruction, and call the function if necessary.
void parse_instruction(char* fmt);

