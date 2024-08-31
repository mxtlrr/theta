ARCH := i386
OBJS := $(wildcard obj/*)

LINK 	 	 := src/linker.ld
LDFLAGS	 := -ffreestanding -O2 -nostdlib

all:
	@mkdir -p obj/ bin/
	@i386-elf-as src/boot/stub.asm -o obj/stub.o
	@echo Adding font as object...
	@i386-elf-ld -r -b binary -o obj/console.o src/console.sfn
	make -C src/kernel || exit
	@echo OBJECTS are $(OBJS)
	i386-elf-gcc -T$(LINK) -o bin/kernel.bin $(LDFLAGS) $(OBJS) -lgcc || exit
	@./build_iso.sh

clean:
	rm -rf obj/ bin/ iso/ theta.iso

QEMU_FLAGS := -d int -M smm=off -monitor stdio -m 256
qemu: theta.iso
	qemu-system-$(ARCH) $(QEMU_FLAGS) -cdrom $^
