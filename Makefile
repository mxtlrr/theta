OBJS := $(wildcard obj/*)

LINK 	 	 := src/linker.ld
LDFLAGS	 := -ffreestanding -O2 -nostdlib

all:
	@mkdir -p obj/ bin/
	@i386-elf-as src/boot/stub.asm -o obj/stub.o
	make -C src/kernel || exit
	make -C initrd || exit
	i386-elf-gcc -T$(LINK) -o bin/kernel.bin $(LDFLAGS) $(OBJS) -lgcc || exit
	@./build_iso.sh