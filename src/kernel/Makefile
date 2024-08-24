INCLUDE := ../../include
CFLAGS := -I$(INCLUDE) -std=gnu99 -ffreestanding -O2

CC := i386-elf-gcc
OBJ := ../../obj/

# We can't compile isr.c without using the specific -mgeneral-regs-only
# "Why not have it for all files?" We use SSE, and -mgeneral-regs-only will
# disable SIMD registers.
override CFILES := $(shell find ./ -type f -name '*.c')
override ASFILES := $(shell find ../../include -type f -name '*.asm')


all:
	@echo SPECIAL -- CC isr.c
	@$(foreach file, $(CFILES), echo CC $(file); $(CC) $(CFLAGS) -c $(file) -o $(OBJ)/$(basename $(notdir $(file))).o;)
	@$(foreach file, $(ASFILES), echo AS $(file); nasm -felf $(file) -o $(OBJ)/$(basename $(notdir $(file))).o;)

clean:
	rm -rf $(OBJ)
