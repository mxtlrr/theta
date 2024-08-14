INCLUDE := ../../include
CFLAGS := -I$(INCLUDE) -std=gnu99 -ffreestanding -O2 \
					-Wall -Wextra

CC := i386-elf-gcc
OBJ := ../../obj/

override CFILES := $(shell find ./ -type f -name '*.c')
override OFILES := $(CFILES:.c=.o)

all:
	@$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o $(OBJ)/$(basename $(notdir $(file))).o; echo CC $(file);)

clean:
	rm -rf $(OBJ)