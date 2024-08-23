all: compile_initrd_gen generate_asm_coff build_initrd 
.PHONY: all

DIRECTORY ?= fs

CC 	   := gcc
CFLAGS := -Wall -Wextra -O3

AS  := nasm
ASF := -fbin

override AS_FILES  := $(shell find ./$(DIRECTORY) -type f -name '*.asm')

generate_asm_coff:
	@mkdir -p obj/asm/ fs/final/
	@$(foreach file, $(AS_FILES), echo BIN $(file); $(AS) $(ASF) $(file) -o fs/final/$(basename $(notdir $(file)));)

compile_initrd_gen:
	@echo CC gen.c
	@$(CC) $(CFLAGS) gen.c -o gen-initrd

build_initrd: gen-initrd
	@./$^ $(DIRECTORY)/final/

clean:
	rm -rf *.img gen-initrd obj/ fs/final