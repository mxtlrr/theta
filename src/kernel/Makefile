INCLUDE := ../../include
CFLAGS := -I$(INCLUDE) -std=gnu99 -ffreestanding -O2

CC := i386-elf-gcc
OBJ := ../../obj/

override CFILES := $(shell find ./ -type f -name '*.c')
override ASFILES := $(shell find ../../include -type f -name '*.asm')

all:
	@$(foreach file, $(CFILES), echo CC $(file); $(CC) $(CFLAGS) -c $(file) -o $(OBJ)/$(basename $(notdir $(file))).o;)
	@$(foreach file, $(ASFILES), echo AS $(file); nasm -felf $(file) -o $(OBJ)/$(basename $(notdir $(file))).o;)

clean:
	rm -rf $(OBJ)