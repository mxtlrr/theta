all: generate_asm_coff
.PHONY: all

DIRECTORY ?= fs

CC 	   := gcc
CFLAGS := -Wall -Wextra -O3 -ffreestanding

AS  := nasm
ASF := -felf


LD  := i386-elf-gcc
LDF := -ffreestanding -O2 -nostdlib

COPIER := i386-elf-objcopy

override AS_FILES  := $(shell find ./$(DIRECTORY) -type f -name '*.asm')
override ELF_FILES := $(shell find ./obj -type f -name '*.elf')

generate_asm_coff:
	@mkdir -p obj/asm/
	@$(foreach file, $(AS_FILES), echo AS $(file); $(AS) $(ASF) $(file) -o obj/asm/$(basename $(notdir $(file))).o; $(LD) $(LDF) obj/asm/$(basename $(notdir $(file))).o -o obj/$(basename $(notdir $(file))).elf;)
	@$(foreach file, $(ELF_FILES), echo COFF $(file); $(COPIER) -O coff-i386 obj/$(basename $(notdir $(file))).elf $(DIRECTORY)/final/$(basename $(notdir $(file))).coff;)

clean:
	rm -rf *.img gen obj/